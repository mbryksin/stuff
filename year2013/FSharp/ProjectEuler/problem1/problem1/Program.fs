
// Matvey Bryksin
// march 2013
// projecteuler.net Problem 1

module problem1.Main

open System

printfn "%A" (Seq.fold (+) 0 (seq { for x in [0..999] -> if x % 3 = 0 || x % 5 = 0 then x else 0 }))