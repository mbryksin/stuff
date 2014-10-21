open System
open System.IO

type private Character(name: string) = 
    member x.Value = name
    override x.Equals y =
        match y with
        | :? Character as y -> x.Value = y.Value
        | _ -> false
    member x.IsVariable = Char.IsUpper(name.[0])
    member x.IsTerminal = not x.IsVariable

//!!!!
    member x.CompateTo (y : Character) = 
            if   name > y.Value then 1
            elif name < y.Value then -1
            else 0

    interface IComparable with
        member x.CompareTo y = x.CompateTo (y :?> Character)
//!!!!

type private Production(left: Character, right: Character list) =
    member x.Left = left
    member x.Right = right
    override x.ToString() = left.Value + " -> " + List.foldBack (fun (x:Character) (acc:string) -> x.Value + " " + acc) right ""

    interface IComparable with
            member x.CompareTo y =
                let rec compareLists (tail1 : Character list) (tail2 : Character list) =
                    match tail1, tail2 with
                    | []     , []      -> 0
                    | _      , []      -> 1
                    | []     , _       -> -1
                    | t1::ts1, t2::ts2 -> let compareT = t1.CompateTo(t2)
                                          if compareT <> 0 then compareT
                                          else compareLists ts1 ts2
                
                let y = y :?> Production
                compareLists (x.Left::x.Right) (y.Left::y.Right)

    override x.Equals y =
        match y with
        | :? Production as y -> x.Left = y.Left && x.Right = y.Right
        | _               -> false
//!!!!

type private Grammar(start: Character, productions: Production list) =
    member x.Start = start
    member x.Productions = productions
    static member CharExists(element, elementsList) = List.exists ((=) element) elementsList
    static member AddUnique(element, elementsList) = match Grammar.CharExists(element, elementsList) with
                                                     | true  -> elementsList
                                                     | false -> element::elementsList    
    
    override x.ToString() = match productions with
                            | [] -> "FAIL"
                            | _  -> List.foldBack (fun (x:Production) (acc:string) -> x.ToString() + "\r\n" + acc) productions ""  
                         
    (*Parsing*)
    static member ParseFromFile(file : String) =
        let text = [yield! File.ReadAllLines(file)]                      
            
        let trim (t : string list) =  List.map (fun (x:string) -> x.Trim([|' '; '\n'|])) t 
            
        let splitProductions (s:string) =[yield! s.Split [|' '|]]

        let createProductions (terms : string list) =
            match terms with
            | x1 :: x2 :: xs when Char.IsUpper(x1.[0]) && x2 = "->" -> 
                Some <| new Production(new Character(x1), List.map (fun s -> new Character(s)) xs)
            | _ -> None
            
        let createGrammar (productions : Production option list) =
            let allSome = List.fold (fun acc x -> acc && match x with
                                                         | Some y -> true
                                                         | None -> false) true productions
            if allSome then 
                let productions = List.map (fun (x: Production option) -> x.Value) productions  
                Some <| new Grammar(productions.Head.Left, productions) 
            else None 

        let grammar = trim text
                    |> List.map splitProductions
                    |> List.map createProductions
                    |> createGrammar 
        grammar

    (*Normalization*)
    static member DeleteEpsilons(g: Grammar) =

        let createRight var var' tail =
            let rec newRight right acc =
                let rec partition p1 p2 =
                    match p2 with
                    | x::xs when (x<>var) -> partition (x::p1) xs
                    | _ -> (List.rev p1),p2
                match right with
                | []::ys -> newRight ys acc
                | y ::ys -> let p1, p2 = partition [] y
                            match p2 with
                            | x::xs -> newRight ((p1@xs)::(p1@(var'::xs))::ys) acc
                            | [] -> newRight ys (y::acc)
                | _      -> acc
            newRight [tail] []

        let deleteProduction productions (var:Character) =
            let newName = var.Value + "#" + Convert.ToString( (new System.Random()).Next(1, 1000) )
            let var' = new Character(newName)
            
            let deleteVariable var var' (p:Production) =
                match p.Left = var with
                | true  -> List.map (fun x -> new Production(var', x)) (createRight var var' p.Right)
                | false -> List.map (fun x -> new Production(p.Left, x)) (createRight var var' p.Right)
                
            let newProductions = List.foldBack (fun x acc -> (deleteVariable var var' x)@acc) productions []
            
            match g.Start = var with
            | true -> (new Production(var, [var']))::newProductions
            | false -> newProductions
            
        let epsilonVariables =
            let rec getVariables acc =
                let newAcc = List.filter (fun (p:Production) -> 
                                            List.fold (fun b c -> b && Grammar.CharExists(c,acc)) true p.Right
                                         ) g.Productions
                            |> List.map (fun p -> p.Left)
                            |> List.fold (fun acc x -> if List.exists ((=) x) acc then acc else x::acc) acc
                if newAcc.Length <> acc.Length then getVariables newAcc else acc
            getVariables []

        let productions = List.fold deleteProduction g.Productions epsilonVariables
        let productions = if Grammar.CharExists(g.Start, epsilonVariables)
                              then Grammar.AddUnique(new Production(g.Start, []), productions) 
                          else productions
        new Grammar(g.Start, productions)


    //---
    static member deleteChains(g:Grammar) =
//!!!!!
        let deleteProduction (prod:Production) (productions:Production list) =
            let rec createNewTails (paths:Character list list) (prods:Production list) acc =
                match paths with
                | (curr::prev)::ps -> 
                    let tails1, tailsN = prods
                                        |> List.filter (fun p -> p.Left = curr)
                                        |> List.map (fun p -> p.Right)
                                        |> List.partition (fun t -> t.Length = 1 && t.Head.IsVariable)      
                    let newPaths = tails1
                                |> List.map List.head
                                |> List.filter (fun c -> not <| List.exists ((=)c) (curr::prev))
                                |> List.map (fun c -> c::curr::prev)
                                |> fun newPs -> newPs @ ps

                    let newAcc = List.fold (fun acc x -> if (List.exists ((=)x) acc) then acc else x::acc) acc tailsN
                    createNewTails newPaths prods newAcc
                | _ -> acc
//!!!!!
            match prod.Right.Length = 1 && prod.Right.Head.IsVariable && prod.Left = prod.Right.Head with
            | true -> [] 
            | false -> createNewTails [[prod.Right.Head; prod.Left]] productions []
                       |> List.map (fun t -> new Production(prod.Left, t))
                       |> fun ps -> ps @ List.filter ((<>)prod) productions

        let rec deleteProductions list =
            let chains = List.tryFind (fun (x:Production) -> x.Right.Length = 1 && x.Right.Head.IsVariable) list
            match chains with
            | Some chain -> deleteProductions (deleteProduction chain list)
            | _          -> list

        new Grammar(g.Start, deleteProductions g.Productions)

    //---
    static member sortAndDeleteDuplicates(grammar : Grammar) =
        
            let rec DeleteDuplicates acc prods =
                match prods with
                | p1::p2::ps -> if p1 = p2 then DeleteDuplicates acc (p2::ps)
                                else DeleteDuplicates (p1::acc) (p2::ps)
                | [p]        -> DeleteDuplicates (p::acc) []
                | _          -> List.rev acc
        
            let newProds = grammar.Productions
                        |> List.sort
                        |> DeleteDuplicates [] 

            let newGrammar = new Grammar(grammar.Start, newProds)

            newGrammar

    //--
    static member deleteNonproductiveProducts(grammar : Grammar) =
        
            ///////////////////////////////////////////////////////////////////////////////////////////

            let rec getProductiveVariables acc =
                let newAcc = grammar.Productions
                            |> List.filter (fun p -> List.forall (fun (c : Character) -> c.IsTerminal || Grammar.CharExists(c,acc)) p.Right)
                            |> List.map (fun p -> p.Left)
                            |> List.fold (fun acc x -> Grammar.AddUnique(x,acc)) acc

                if newAcc.Length <> acc.Length then getProductiveVariables newAcc else acc
        
            ///////////////////////////////////////////////////////////////////////////////////////////

            let productiveVars = getProductiveVariables []

            let newProds = grammar.Productions
                        |> List.filter (fun p -> Grammar.CharExists(p.Left,productiveVars) )
                        |> List.filter (fun p -> List.forall (fun (c : Character) -> c.IsTerminal || Grammar.CharExists(c,productiveVars)) p.Right)
            let newGrammar = new Grammar(grammar.Start, newProds)

            newGrammar
    
    //---
    static member deleteUnattainableProducts(grammar : Grammar) =
        
            ///////////////////////////////////////////////////////////////////////////////////////////

            let rec getAttainableVariables curr acc =
                match curr with
                | c::cs -> grammar.Productions
                        |> List.filter (fun p -> p.Left = c)
                        |> List.map (fun p -> p.Right)
                        |> List.concat
                        |> List.filter (fun c -> c.IsVariable)
                        |> List.filter (fun c -> not <| Grammar.CharExists(c,acc))
                        |> fun a -> getAttainableVariables (a@cs) (c::acc)
                | _     -> acc

        
            ///////////////////////////////////////////////////////////////////////////////////////////

            let attainableVars = getAttainableVariables [grammar.Start] []

            let newProds = grammar.Productions
                        |> List.filter (fun p -> Grammar.CharExists(p.Left,attainableVars))
                        |> List.filter (fun p -> List.forall (fun (c : Character) -> c.IsTerminal || Grammar.CharExists(c,attainableVars)) p.Right)
            let newGrammar = new Grammar(grammar.Start, newProds)

            newGrammar         
          
        ///////////////////////////////////////////////////////////////////////////////////////////

    static member removeTerminalsAndLongTails(grammar : Grammar) =
        
            let rec splitTail left (right : Character list) =
                match right with
                | r::rs when r.IsVariable -> splitTail (r::left) rs
                | _                       -> List.rev left, right
        
            let rec removeTermssAndLongTails (prods : Production list) acc =
                match prods with
                | p::ps when p.Right.Length <= 1 -> removeTermssAndLongTails ps (p::acc)
                | p::ps -> let left, right = splitTail [] p.Right
                           if right.IsEmpty && p.Right.Length = 2 then removeTermssAndLongTails ps (p::acc)
                           else 
                                let newName = "S!" + Convert.ToString( (new System.Random()).Next(1, 1000) )
                                let newVar = new Character(newName)

                                let p1, p2 = 
                                    if not right.IsEmpty then      
                                        new Production(p.Left, left @ (newVar::right.Tail)),
                                        new Production(newVar, [right.Head])
                                    else 
                                        new Production(newVar, p.Right.Tail),
                                        new Production(p.Left, [p.Right.Head; newVar])

                                removeTermssAndLongTails (p1::ps) (p2::acc)
                | _     -> acc

            let newProds = removeTermssAndLongTails grammar.Productions []
            let newGrammar = new Grammar(grammar.Start, newProds)

            newGrammar

        ///////////////////////////////////////////////////////////////////////////////////////////

    static member moveAxiomUp (grammar : Grammar) =
            let rec moveAxUp left (right : Production list) =
                match right with
                | r::rs when r.Left = grammar.Start -> r::(List.rev left @ rs)
                | r::rs                             -> moveAxUp (r::left) rs
                | _ -> []

            if grammar.Productions.IsEmpty then grammar
            else let newProds = moveAxUp [] grammar.Productions
                 let newGrammar = new Grammar(grammar.Start, newProds)
                 newGrammar
    //--
    static member ToCNF(g: Grammar) =
        Grammar.DeleteEpsilons(g)
        |> Grammar.deleteChains
        |> Grammar.sortAndDeleteDuplicates
        |> Grammar.deleteNonproductiveProducts
        |> Grammar.deleteUnattainableProducts
        |> Grammar.removeTerminalsAndLongTails
        |> Grammar.sortAndDeleteDuplicates
        |> Grammar.moveAxiomUp
//!!!!!
            
[<EntryPoint>]
let main argv = 
    let G = Grammar.ParseFromFile "../../tests/cnf02.g"
    let cnfG = Grammar.ToCNF(G.Value)
    printfn "%A" cnfG
    0
    (*
    if argv.Length <> 1 then printfn "Incorrect arguments"
        else try let gramOpt = Grammar.ParseFromFile argv.[0] 
                 gramOpt
             with
             | :? FileNotFoundException -> printfn "File not found"
    0
    *)
