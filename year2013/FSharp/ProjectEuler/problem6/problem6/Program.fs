
// NOTE: If warnings appear, you may need to retarget this project to .NET 4.0. Show the Solution
// Pad, right-click on the project node, choose 'Options --> Build --> General' and change the target
// framework to .NET 4.0 or .NET 4.5.

module problem6.Main

open System

let N = 100
let p = Seq.fold (+) 0 (seq {for x in [1..N] -> x})
let q = Seq.fold (+) 0 (seq {for x in [1..N] -> x*x})
let result = (-) (p * p) q
printfn "Result = %d" result
