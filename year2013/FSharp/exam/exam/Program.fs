
// By Matvey Bryksin
// the 22th of April

open System

type Monomial = float * int

type Polinomial = 
  | Element of Monomial * Polinomial
  | Empty

let rec insert factor degree pol =
  match pol with
  | Empty -> Element((factor, degree), Empty)
  | Element((fact, deg), tail) when deg > degree -> Element((fact, deg), insert factor degree tail)
  | Element((fact, deg), tail) when deg < degree -> Element((factor, degree), insert fact deg tail)
  | Element((fact, deg), tail) when deg = degree -> Element((factor + fact, degree), tail)
  | _ -> Empty
  
let mutable pol = 
  Empty
  |> insert 0.0 2
  |> insert -20.0 3
  |> insert -10.0 3
  |> insert 1.1 1
  |> insert 17.32 0
  |> insert -25.0 5
  |> insert 1.0 4

let printPolinomial pol =
  let rec printPol pol k =
    match pol with
    | Empty -> printfn ""
    | Element((fact, deg), tail) ->
      if fact <> 0.0 then
        if fact > 0.0
          then if (k <> 0) then printf "+ "
          else printf "- "
        if deg = 1
          then printf "%g*x " (Math.Abs fact)
          else 
            if deg = 0
              then printf "%g " (Math.Abs fact)
              else 
                if (Math.Abs fact) = 1.0 
                  then printf "x^%d " deg
                  else printf "%g*x^%d " (Math.Abs fact) deg
      printPol tail 1
  printPol pol 0

printfn "Polinomial 1:"  
printPolinomial pol 

let rec multConst pol (c:float) =
  match pol with
  | Empty -> Empty
  | Element((fact, deg), tail) -> Element((fact * c, deg), multConst tail c)

pol <- multConst pol -1.0

printfn "Polinomial 1 after multiply on -1:"
printPolinomial pol 

let mutable pol2 = 
  Empty
  |> insert 5.4 10
  |> insert 24.23 2
  |> insert 3.21 11
  |> insert 10.0 0
  |> insert -10.0 3

printfn "Polinomial 2:"
printPolinomial pol2

let rec addPol pol1 pol2 =
  match pol1 with
  | Empty -> pol2
  | Element((fact1, deg1), tail1) ->
    match pol2 with
    | Empty -> pol1
    | Element((fact2, deg2), tail2) ->
      if deg1 = deg2
        then Element((fact1 + fact2, deg1), addPol tail1 tail2)
        else
          if deg1 > deg2
            then Element((fact1, deg1), addPol tail1 pol2)
            else Element((fact2, deg2), addPol pol1 tail2)

printfn "After addition 1 with 2"            
printPolinomial (addPol pol pol2)