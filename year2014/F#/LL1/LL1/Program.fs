open System
open System.Collections
open System.Collections.Generic
open System.IO

type Character(name: string) = 
    let mutable first = []
    let mutable follow = []
    let mutable epsilonCreated = false
    let mutable epsViewed = false
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
    member this.EpsilonCreated
        with get () = epsilonCreated
        and set (value) = epsilonCreated <- value

    member this.EpsilonViewed
        with get () = epsViewed
        and set (value) = epsViewed <- value

    interface IComparable with
        member x.CompareTo y = x.Compare (y :?> Character)

    member x.Compare (y : Character) = 
        if name > y.Value then 1
        else if name < y.Value then -1
        else 0

type Production(left: Character, right: Character list) =
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

////--------------
type Rule = Null | Error | Prod of Production 
          with

    member x.IsErr = match x with
                     | Error -> true
                     | _     -> false

    member x.IsEmpty = match x with
                       | Null -> true
                       |_     -> false

    member x.Value = match x with
                     | Prod p -> p
////--------------

type Table(nonterms : Character list, terms : Character list) =
  class
    let NonTermIndex = Dictionary<Character, int>()
    let TermIndex = Dictionary<Character, int>()
    let table = Array2D.create (List.length nonterms) ((List.length terms) + 1) Null

    do nonterms |> List.iteri (fun i v -> NonTermIndex.Add(v, i))
       terms    |> List.iteri (fun i t -> TermIndex.Add(t, i))

    member x.Item 
        with get(v, t) = let mutable i = NonTermIndex.[v]
                         let j = ref -1
                         Seq.iter (fun (x:KeyValuePair<Character,int>) -> if (x.Key = t) then j := x.Value) TermIndex
                         table.[i, !j]
             and set(v, t) a = match table.[NonTermIndex.[v], TermIndex.[t]] with
                               | Null -> table.[NonTermIndex.[v], TermIndex.[t]] <- Prod a
                               | Prod p when p = a -> ()
                               | _ -> table.[NonTermIndex.[v], TermIndex.[t]] <- Error

    member x.IsError =
        let mutable isError = false 
        for i = 0 to Array2D.length1 table - 1 do
            for j = 0 to Array2D.length2 table - 1 do
                isError <- isError || table.[i,j].IsErr

        isError

  end

type Grammar(start: Character, productions: Production list, chars: Character list) =
    let eps = new Character("Eps")
    let fail = new Character("FAIL")
    let ok = new Character("OK")
    let endsym = new Character("$")
    
    member x.Start = start
    member x.Productions = productions
    member this.CharList = chars
    
    member this.Eps = eps
    member this.Ok = ok
    member this.Fail = fail
    member this.End = endsym
      
    static member CharExists(element, elementsList) = List.exists ((=) element) elementsList
    static member AddUnique(element, elementsList) = match Grammar.CharExists(element, elementsList) with
                                                     | true  -> elementsList
                                                     | false -> element::elementsList    
    (*Parsing grammar text*)
    static member ParseFromFile(file : String) =
        let text = [yield! File.ReadAllLines(file)]                      
            
        let trim (t : string list) = List.filter ((<>)"") (List.map (fun (x:string) -> x.Trim([|' '; '\n'; '\r'|])) t)
            
        let splitProductions (s:string) = [yield! s.Split [|' '|]]

        let createProductions (terms: string list list) = 
            let chars = ref []
            
            let NewCharacter(name) =
                let unique = List.filter (fun (x:Character) -> x.Value = name) !chars
                if List.isEmpty unique
                 then let nchar = new Character(name)
                      chars := nchar::!chars
                      nchar
                 else
                    List.head unique
            
            let ps = terms |> List.map (fun p -> match p with
                                                 | x1 :: x2 :: xs when Char.IsUpper(x1.[0]) && x2 = "->" -> 
                                                        Some <| new Production(NewCharacter(x1), List.map (fun s -> NewCharacter(s)) xs)
                                                 | _ -> None )
            (ps,!chars)

            
        let createGrammar (pair) =
            match pair with
            | (productions, charlist) -> let allSome = List.fold (fun acc x -> acc && match x with
                                                                                      | Some y -> true
                                                                                      | None -> false) true productions
                                         if allSome 
                                            then let productions = List.map (fun (x: Production option) -> x.Value) productions  
                                                 Some <| new Grammar(productions.Head.Left, productions, charlist) 
                                            else None

        let grammar = trim text
                    |> List.map splitProductions
                    |> createProductions
                    |> createGrammar 
        grammar

    
    static member Analyse(g: Grammar, input:string) =
        let rec createdEpsilon (var:Character) =
            if not(var.EpsilonViewed) 
            then
                var.EpsilonViewed <- true
                List.iter (fun (p:Production) -> if (p.Left=var) 
                                                    then if p.Right.IsEmpty 
                                                            then var.EpsilonCreated <- true
                                                            else
                                                                p.Right |> List.iter (fun v -> if v.IsVariable then createdEpsilon v) 
                                                                var.EpsilonCreated <- var.EpsilonCreated || (List.fold(fun acc (v:Character) -> v.EpsilonCreated && acc) true p.Right)
                          ) g.Productions
                
                
        let rec first var =
            let rec firstRight acc (list: Character list) =
                match list with
                | [] -> acc
                | x::xs when x.IsTerminal -> Grammar.AddUnique(x,acc)
                | x::xs when x.IsVariable -> first x
                                             if x.EpsilonCreated
                                                then let step = List.fold (fun acc2 x -> Grammar.AddUnique(x,acc2)) x.FIRST acc
                                                     firstRight step xs
                                                else List.fold (fun acc2 x -> Grammar.AddUnique(x,acc2)) x.FIRST acc

            List.iter (fun (p:Production) -> if (p.Left=var) 
                                                then if p.Right.IsEmpty 
                                                        then var.FIRST <- Grammar.AddUnique(g.Eps,var.FIRST) 
                                                        else
                                                            var.FIRST <- List.fold (fun acc x -> Grammar.AddUnique(x,acc)) var.FIRST (firstRight [] p.Right) 
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
       
        let rec parseNext (table:Table) (stack:Stack<Character>) str acc =
            let charPop = stack.Pop()
            try match str, charPop with
                    | hd::[], c -> if hd = g.End && hd = c then g.Ok :: acc else g.Fail :: acc 
                    | hd::tl, c when c.IsTerminal -> if hd = c then parseNext table stack tl (c :: acc) else g.Fail :: acc 
                    | hd::tl, v when v.IsVariable -> let rule = table.[v, hd]
                                                     if rule.IsEmpty 
                                                         then g.Fail :: acc 
                                                         else let t = rule.Value
                                                              List.iter stack.Push (List.rev t.Right)
                                                              parseNext table stack str (v :: acc)
                    | _ -> g.Fail :: acc
            with _ -> g.Fail :: acc        

        let follow (p:Production) =                  
            let rec findFollows (A:Character) (acc:Character list) = 
                let rec firstRight acc (list: Character list) =
                    match list with
                    | [] -> acc
                    | x::xs when x.IsTerminal -> Grammar.AddUnique(x,acc)
                    | x::xs when x.IsVariable -> if x.EpsilonCreated
                                                    then let step = List.fold (fun acc2 x -> Grammar.AddUnique(x,acc2)) x.FIRST acc
                                                         firstRight step xs
                                                    else List.fold (fun acc2 x -> Grammar.AddUnique(x,acc2)) x.FIRST acc

                match acc with
                | X::[] when X.IsVariable -> X.FOLLOW <- List.fold (fun acc x -> Grammar.AddUnique(x,acc)) X.FOLLOW A.FOLLOW 
                | X::xs when X.IsTerminal -> findFollows A xs
                | X::beta when X.IsVariable -> let betaFirst = firstRight [] beta
                                               X.FOLLOW <- List.fold (fun acc x -> Grammar.AddUnique(x,acc)) X.FOLLOW (List.filter ((<>)g.Eps) betaFirst)
                                               if Grammar.CharExists(g.Eps,betaFirst)
                                                   then X.FOLLOW <- List.fold (fun acc x -> Grammar.AddUnique(x,acc)) X.FOLLOW A.FOLLOW  
                                               findFollows A beta                     
                | _ -> ignore ""        
             
            findFollows p.Left p.Right

        let rec follows vs =
            let oldVars = List.foldBack (fun (v:Character) acc -> let c = new Character(v.Value)
                                                                  c.EpsilonViewed <- v.EpsilonViewed
                                                                  c.FIRST <- v.FIRST
                                                                  c.EpsilonCreated <- v.EpsilonCreated
                                                                  c.FOLLOW <- v.FOLLOW
                                                                  c::acc 
                                        ) vs []
            List.iter (fun p -> follow p) g.Productions
            let restart = List.fold (fun acc (v:Character) -> (List.fold (fun acc2 (x:Character) -> if x=v 
                                                                                                      then x.FOLLOW.Length <> v.FOLLOW.Length 
                                                                                                      else acc2 
                                                                         ) false oldVars) || acc 
                                    ) false vs 
            if restart then follows vs

        
        let vars = List.fold (fun acc (x:Production) -> List.fold (fun acc2 (y:Character) -> if y.IsVariable then Grammar.AddUnique(y,acc2) else acc2) (if x.Left.IsVariable then Grammar.AddUnique(x.Left,acc) else acc) x.Right
                             ) [] g.Productions
        let terms = List.fold (fun acc (x:Production) -> List.fold (fun acc2 (y:Character) -> if y.IsTerminal then Grammar.AddUnique(y,acc2) else acc2) acc x.Right
                             ) [] g.Productions

        List.iter (fun v -> createdEpsilon v) vars
        
        firsts vars
        vars |> List.iter (fun x -> if not(x.EpsilonCreated) then x.FIRST <- List.filter ((<>)g.Eps) x.FIRST )
        
        g.Start.FOLLOW <- Grammar.AddUnique(g.End,g.Start.FOLLOW)
        follows vars
                                                    
        let terms = g.End::(List.filter (fun (x:Character) -> x.IsTerminal ) g.CharList)
        let nonterms = List.filter (fun (x:Character) -> x.IsVariable ) g.CharList
        let table = new Table(nonterms, terms)
        
        g.Productions |> List.iter (fun p -> let firstsProdRight = ref []
                                             let mutable tail = p.Right
                                             let mutable flag = true
                                             while flag && not (List.isEmpty tail) do
                                                match tail with
                                                | x::xs when x.IsTerminal -> firstsProdRight := Grammar.AddUnique(x,!firstsProdRight)
                                                                             flag <- false
                                                | x::xs when x.IsVariable -> if x.EpsilonCreated
                                                                             then List.iter (fun x -> firstsProdRight := Grammar.AddUnique(x,!firstsProdRight)) x.FIRST
                                                                                  tail <- xs
                                                                             else List.iter (fun x -> firstsProdRight := Grammar.AddUnique(x,!firstsProdRight)) x.FIRST
                                                                                  flag <- false
                                             firstsProdRight := List.filter (fun (x:Character) -> x <> g.Eps) !firstsProdRight
                   
                                             !firstsProdRight |> List.iter (fun t -> table.[p.Left, t] <- p)
                                             let eps = p.Right.IsEmpty || List.fold (fun acc3 (x:Character) -> acc3 && x.EpsilonCreated) true p.Right
                                             if eps then p.Left.FOLLOW |> Seq.iter (fun t -> table.[p.Left, t] <- p)
                                   )
        
        let str = input.Split([|'\n'; '\r'; '\t'; ' '|]) |> String.concat ""
                                                         |> fun s -> s.ToCharArray()
                                                         |> Array.map (fun c -> new Character(string c))
                                                         |> List.ofArray
        
        if table.IsError then [g.Fail]
        else
            let stack = new Stack<Character>()
            stack.Push(g.End)
            stack.Push(g.Start)
            List.rev <| parseNext table stack (str @ [g.End]) [] 

        
            
[<EntryPoint>]
let main argv = 
    if argv.Length <> 2 then printfn "Incorrect arguments"
        else try 
                 let G = Grammar.ParseFromFile argv.[0]
                 let reader = new StreamReader(argv.[1])
                 let inputStr = reader.ReadToEnd()
                 Grammar.Analyse(G.Value, inputStr)
                    |> List.map (fun x -> x.Value)
                    |> String.concat " "
                    |> printf "%s"
             with
             | :? FileNotFoundException -> printfn "Error"
    0
