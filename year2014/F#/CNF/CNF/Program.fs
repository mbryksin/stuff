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

    interface IComparable with
        member x.CompareTo y = x.Compare (y :?> Character)

    member x.Compare (y : Character) = 
        if name > y.Value then 1
        else if name < y.Value then -1
        else 0

type private Production(left: Character, right: Character list) =
    member x.Left = left
    member x.Right = right
    override x.ToString() = left.Value + " -> " + List.foldBack (fun (x:Character) (acc:string) -> x.Value + " " + acc) right ""

    interface IComparable with
        member x.CompareTo y =
            let rec compareLists (t1 : Character list) (t2 : Character list) =
                match t1, t2 with
                | [],[] -> 0
                | _,[] -> 1
                | [],_ -> -1
                | x::xs, y::ys -> let res = x.Compare(y)
                                  match res with
                                  | 0 -> compareLists xs ys
                                  | _ -> res
            compareLists (x.Left::x.Right) ((y :?> Production).Left::(y :?> Production).Right)

    override x.Equals y =
        match y with
        | :? Production as y -> x.Left = y.Left && x.Right = y.Right
        | _ -> false

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
            let var' = new Character(var.Value + "#" + Convert.ToString( (new System.Random()).Next(1, 1000) ))
            
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


    static member deleteChains(g:Grammar) =
        let deleteProduction (prod:Production) (productions:Production list) =
            let rec createProductions (paths:Character list list) (prods:Production list) acc =
                match paths with
                | (x::y)::ps -> 
                    let t1, t2 = List.filter (fun (p:Production) -> p.Left = x) prods
                                        |> List.map (fun p -> p.Right)
                                        |> List.partition (fun t -> t.Length = 1 && t.Head.IsVariable)      
                    let paths = List.map List.head t1
                                |> List.filter (fun c -> not(List.exists ((=)c) (x::y)))
                                |> List.map (fun c -> c::x::y)
                                |> fun x -> x @ ps

                    let acc = List.fold (fun acc x -> if (List.exists ((=)x) acc) then acc else x::acc) acc t2
                    createProductions paths prods acc
                | _ -> acc

            match prod.Right.Length = 1 && prod.Right.Head.IsVariable && prod.Left = prod.Right.Head with
            | true -> [] 
            | false -> createProductions [[prod.Right.Head; prod.Left]] productions []
                       |> List.map (fun x -> new Production(prod.Left, x))
                       |> fun x -> x @ List.filter ((<>)prod) productions

        let rec deleteProductions list =
            let chains = List.tryFind (fun (x:Production) -> x.Right.Length = 1 && x.Right.Head.IsVariable) list
            match chains with
            | Some chain -> deleteProductions (deleteProduction chain list)
            | _          -> list

        new Grammar(g.Start, deleteProductions g.Productions)

    static member sortClean(g: Grammar) = 
        let rec deleteDoubles prods acc =
                match prods with
                | p1::p2::ps -> match p1 = p2 with
                                | true -> deleteDoubles (p2::ps) acc
                                | false -> deleteDoubles  (p2::ps) (p1::acc)
                | [x]        -> deleteDoubles [] (x::acc)
                | _          -> List.rev acc
        
        new Grammar(g.Start, deleteDoubles (List.sort g.Productions) [] )

    static member deleteUnnecessaryProducts(g:Grammar) =
        let rec findProductive acc =
            let tmp = g.Productions
                    |> List.filter (fun p -> List.forall (fun (c:Character) -> c.IsTerminal || Grammar.CharExists(c,acc)) p.Right)
                    |> List.map (fun p -> p.Left)
                    |> List.fold (fun acc x -> Grammar.AddUnique(x,acc)) acc
            match acc.Length <> tmp.Length with
            | true  -> findProductive tmp 
            | false -> acc
         
        let rec findAttainable list acc =
            match list with
            | x::xs -> g.Productions
                    |> List.filter (fun p -> p.Left = x)
                    |> List.map (fun p -> p.Right)
                    |> List.concat
                    |> List.filter (fun c -> c.IsVariable)
                    |> List.filter (fun c -> not(Grammar.CharExists(c,acc)) )
                    |> fun y -> findAttainable (y@xs) (x::acc)
            | _     -> acc

        let productions = List.filter (fun (x:Production) -> Grammar.CharExists(x.Left,findProductive [])) g.Productions
                        |> List.filter (fun x -> List.forall (fun (c:Character) -> c.IsTerminal || Grammar.CharExists(c,findProductive [])) x.Right)
                        |> List.filter (fun x -> Grammar.CharExists(x.Left,findAttainable [g.Start] []))
                        |> List.filter (fun x -> List.forall (fun (c:Character) -> c.IsTerminal || Grammar.CharExists(c,findAttainable [g.Start] [])) x.Right)
        
        new Grammar(g.Start, productions)  


    static member shorten(g: Grammar) =
        let rec splits left (right : Character list) =
            match right with
            | x::xs when x.IsVariable -> splits (x::left) xs
            | _                       -> List.rev left, right
        
        let rec remove (list:Production list) acc =
            match list with
            | x::xs when x.Right.Length <= 1 -> remove xs (x::acc)
            | x::xs -> let left, right = splits [] x.Right
                       match right.IsEmpty && x.Right.Length = 2 with
                       | true -> remove xs (x::acc)
                       | _ -> let var = new Character("S!" + Convert.ToString( (new System.Random()).Next(1, 1000) ))
                              match right.IsEmpty with
                              | true -> remove ((new Production(var, x.Right.Tail))::xs) ((new Production(x.Left, [x.Right.Head; var]))::acc)
                              | false -> remove ((new Production(x.Left, left @ (var::right.Tail)))::xs) ((new Production(var, [right.Head]))::acc)
            | _     -> acc

        new Grammar(g.Start, remove g.Productions [])

    static member newAxiom (g:Grammar) =
            let rec lift left (right:Production list) =
                match right with
                | x::xs when x.Left = g.Start -> x::(List.rev left@xs)
                | x::xs -> lift (x::left) xs
                | _ -> []

            match g.Productions with
            | [] -> g
            | _  -> new Grammar(g.Start, lift [] g.Productions)

    static member ToCNF(g: Grammar) =
        Grammar.DeleteEpsilons(g)
        |> Grammar.deleteChains
        |> Grammar.sortClean
        |> Grammar.deleteUnnecessaryProducts
        |> Grammar.shorten
        |> Grammar.sortClean
        |> Grammar.newAxiom

            
[<EntryPoint>]
let main argv = 
    (*
    let G = Grammar.ParseFromFile "../../tests/cnf01.g"
    let cnfG = Grammar.ToCNF(G.Value)
    printfn "%A" cnfG
    0
    *)
    if argv.Length <> 1 then printfn "Incorrect arguments"
        else try let g = Grammar.ParseFromFile argv.[0]
                 match g with
                 | None -> printfn "FAIL"
                 | Some x -> printfn "%A" <| Grammar.ToCNF(x)
             with
             | :? FileNotFoundException -> printfn "File not found"
    0
    
