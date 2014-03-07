
// by MatveyBryksin
// the 5th of April
// projecteuler.net Problem10

open System

let N = 2000000
let mutable sieve = [2]
let mutable i = 3

let f x y =
  if x % y = 0 then false else true
  
let sum x y = 
  (int64 x) + (int64 y)

let rec isPrime x sieve = 
  match sieve with
  | [] -> true
  | head::tail -> (isPrime x tail) && (f x head)
  
while ( i < N ) do
 if (isPrime i sieve) 
   then sieve <- (List.append sieve [i])
 i <- i + 1

printfn "%A" <| List.fold sum 0L sieve