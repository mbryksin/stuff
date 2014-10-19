open System
open System.IO

type private Character(name: string) = 
    member x.Value = name

type private Production(left: Character, right: Character list) =
    member x.Left = left
    member x.Right = right
     

type private Grammar(start: Character, productions: Production list) =
    member x.Start = start
    member x.Productions = productions
    
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
            
[<EntryPoint>]
let main argv = 
    let g = Grammar.ParseFromFile "../../cnf00.g"
    0
    
    (*
    if argv.Length <> 1 then printfn "Incorrect arguments"
        else try let gramOpt = Grammar.ParseFromFile argv.[0] 
                 gramOpt
             with
             | :? FileNotFoundException -> printfn "File not found"
    0
    *)
