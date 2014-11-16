open System
open System.IO

type private Character(name: string) = 
    let mutable first = []
    let mutable follow = []
    member x.Value = name
    override x.Equals y =
        match y with
        | :? Character as y -> x.Value = y.Value
        | _ -> false
    member x.IsVariable = Char.IsUpper(name.[0])
    member x.IsTerminal = not x.IsVariable

    member this.FIRST
        with get () = first
        and set (value) = first <- value
    member this.FOLLOW
        with get () = follow
        and set (value) = follow <- value

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
    let eps = new Character("Epsilon")
    member this.Eps
        with get () = eps
    member x.Start = start
    member x.Productions = productions
    static member CharExists(element, elementsList) = List.exists ((=) element) elementsList
    static member AddUnique(element, elementsList) = match Grammar.CharExists(element, elementsList) with
                                                     | true  -> elementsList
                                                     | false -> element::elementsList    
                      
    (*Parsing*)
    static member ParseFromFile(file : String) =
        let text = [yield! File.ReadAllLines(file)]                      
            
        let trim (t : string list) = List.filter ((<>)"") (List.map (fun (x:string) -> x.Trim([|' '; '\n'; '\r'|])) t)
            
        let splitProductions (s:string) = [yield! s.Split [|' '|]]

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

    
    static member Analyse(g: Grammar) = 
        let rec first var =
                List.iter (fun (p:Production) -> if (p.Left=var) 
                                                    then if p.Right.IsEmpty 
                                                         then var.FIRST <- Grammar.AddUnique(g.Eps,var.FIRST) 
                                                         else if p.Right.Head.IsTerminal 
                                                                 then var.FIRST <- Grammar.AddUnique(p.Right.Head, var.FIRST)
                                                                 else 
                                                                     first p.Right.Head
                                                                     var.FIRST <- List.fold (fun acc x -> Grammar.AddUnique(x,acc)) var.FIRST p.Right.Head.FIRST 
                           ) g.Productions
        
        let rec firsts vs =
            let oldVars = List.foldBack (fun (v:Character) acc -> let c = new Character(v.Value)
                                                                  c.FIRST <- v.FIRST
                                                                  c::acc 
                                        ) vs []
            List.iter (fun v -> first v) vs
            let restart = List.fold (fun acc (v:Character) -> (List.fold (fun acc2 (x:Character) -> if x=v 
                                                                                                      then x.FIRST.Length <> v.FIRST.Length 
                                                                                                      else acc2 
                                                                         ) false oldVars) || acc 
                                    ) false vs 
            if restart then firsts vs

        let rec follows vs =
        //отслеживать несколько вхождений переменной в продукцию
        //отслеживать выводимость эпсилона из следующей переменной 
            let rec follow var =
                let rec findFollowVar var (p:Production) =
                    let rec findNext var (acc:Character list) = 
                        match acc with
                        | x::y::xs when (x = var) -> if y.IsTerminal 
                                                        then [y]
                                                        else first y
                                                             List.filter ((<>)g.Eps) y.FIRST
                        | x::[] when (x = var) -> follow p.Left
                                                  p.Left.FOLLOW
                        | x::y -> findNext var y
                        | _ -> []
                    findNext var p.Right

                List.iter (fun (p:Production) -> if (List.exists ((=)var) p.Right) 
                                                    then var.FOLLOW <- List.fold (fun acc x -> Grammar.AddUnique(x,acc)) var.FOLLOW (findFollowVar var p)
                           ) g.Productions

            let oldVars = List.foldBack (fun (v:Character) acc -> let c = new Character(v.Value)
                                                                  c.FIRST <- v.FIRST
                                                                  c::acc 
                                        ) vs []
            List.iter (fun v -> follow v) vs
            let restart = List.fold (fun acc (v:Character) -> (List.fold (fun acc2 (x:Character) -> if x=v 
                                                                                                      then x.FIRST.Length <> v.FIRST.Length 
                                                                                                      else acc2 
                                                                         ) false oldVars) || acc 
                                    ) false vs 
            if restart then firsts vs

        
        let vars = List.fold (fun acc (x:Production) -> List.fold (fun acc2 (y:Character) -> if y.IsVariable then Grammar.AddUnique(y,acc2) else acc2) (if x.Left.IsVariable then Grammar.AddUnique(x.Left,acc) else acc) x.Right
                             ) [] g.Productions
        let terms = List.fold (fun acc (x:Production) -> List.fold (fun acc2 (y:Character) -> if y.IsTerminal then Grammar.AddUnique(y,acc2) else acc2) acc x.Right
                             ) [] g.Productions
        List.iter (fun (v:Character) -> v.FIRST <- []) vars
        firsts vars
        follows vars

        vars                                                      
        
            
[<EntryPoint>]
let main argv = 
    let G = Grammar.ParseFromFile "../../tests/g2.g"
    let R = Grammar.Analyse(G.Value)
    printfn "%A" R
    0
    (*
    if argv.Length <> 1 then printfn "Incorrect arguments"
        else try let g = Grammar.ParseFromFile argv.[0]
                 match g with
                 | None -> printfn "FAIL"
             with
             | :? FileNotFoundException -> printfn "File not found"
    0
    *)
