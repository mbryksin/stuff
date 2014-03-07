
// NOTE: If warnings appear, you may need to retarget this project to .NET 4.0. Show the Solution
// Pad, right-click on the project node, choose 'Options --> Build --> General' and change the target
// framework to .NET 4.0 or .NET 4.5.

module problem72.Main

open System

let d' = 13
let f x y =
  let c = ref 1
  for h in [2..x] do
    if x % h = 0 && y % h = 0 then c := 0
  !c
    
let ll =
  seq { for i in [2..d'] do 
        for j in [1..i-1] do
          if (not(i % j = 0) || (j = 1)) && (f j i = 1) then yield (j,i) }

let i = ref 0
for (x,y) in ll do 
  incr i

printfn "Number: %A" !i
printfn "Fractions:"
Seq.iter (fun (a,b) -> printf "%d/%d " a b) (ll)