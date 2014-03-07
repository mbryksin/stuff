// NOTE: If warnings appear, you may need to retarget this project to .NET 4.0. Show the Solution
// Pad, right-click on the project node, choose 'Options --> Build --> General' and change the target
// framework to .NET 4.0 or .NET 4.5.

module problem36.Main

open System

let N = 1000000

let pal num =
  let x = ref num
  let digs = ref 0
  let ll = [| while (!x > 0) do yield !x % 10; x := !x / 10; incr digs done |]
  let c = ref 1
  for i = 0 to (!digs - 1) / 2 do
    if not(ll.[i] = ll.[!digs - 1 - i]) then c := 0
  !c

let bin x =
  let mutable t = x
  let mutable ll = Array.empty 
  let digs = ref 0
  while (t >= 1) do
    if (t % 2 = 0) then ll <- Array.append ll [|0|] else ll <- Array.append ll [|1|]
    incr digs
    t <- t / 2
  let c = ref 1
  for i = 0 to (!digs - 1) / 2 do
    if not(ll.[i] = ll.[!digs - 1 - i]) then c := 0
  !c 
        
let f =
  let mutable col = Seq.empty
  for x in seq { for x in [1..N] -> x} do
    let y = seq { yield x } 
    if pal x = 1 then if bin x = 1 then col <- Seq.append col y 
  col  

printfn "%A" <| Seq.fold (+) 0 f    
//Seq.iter (fun a -> printfn "%d " a) f
