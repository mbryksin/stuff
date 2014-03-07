
// by Matvey Bryksin
// the 1st of April
// projecteuler.net Problem 4 

//module problem4.Main

open System

let isPalindrome number =
  let str = number.ToString()
  let N = String.length str
  let mutable l = true
  let mutable i = 0
  for i = 0 to N - 1 do
    if str.[i] <> str.[N-i-1] then l <- false
  l

let mutable x = 10000
let mutable i = 100
let mutable j = 100
for i in [100..999] do
  for j in [100..999] do
    if isPalindrome (i*j) then 
      if i*j > x then x <- (i*j)
printfn "%A" x