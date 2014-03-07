
// by Matvey Bryksin 171 group
// the 5th of April 2013
// projecteuler.net Problem 9

open System

let f a b c = 
  if a*a + b*b = c*c
    then true
    else false

let sum = seq { for a in [1..999] do for b in [a+1..999] do if (f a b (1000-a-b)) then yield(a*b*(1000-a-b))}
printfn "%A" <| Seq.max sum
             