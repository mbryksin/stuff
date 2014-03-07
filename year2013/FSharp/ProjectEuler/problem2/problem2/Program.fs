
// NOTE: If warnings appear, you may need to retarget this project to .NET 4.0. Show the Solution
// Pad, right-click on the project node, choose 'Options --> Build --> General' and change the target
// framework to .NET 4.0 or .NET 4.5.

module problem2.Main

open System

let N = 4000000
let mutable x = 2
let mutable y = 1
let mutable sum = 0
while x < N do
  x <- x + y
  y <- x - y
  if y % 2 = 0 then sum <- sum + y
printfn "result = %d" sum