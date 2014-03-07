
// by Matvey Bryksin
// the 4nd of April (!)
// projecteuler.net Problem 7

open System

let N = 10001
let mutable count = 2
let mutable sieve = [2;3]
let mutable i = 4

let f x y =
  if x % y = 0 then false else true

let rec isPrime x sieve = 
  match sieve with
  | [] -> true
  | head::tail -> (isPrime x tail) && (f x head)
  
while ( count < N ) do
 if (isPrime i sieve) 
   then count <- count + 1
        sieve <- (List.append sieve [i])
   else count <- count
 i <- i + 1

sieve <- List.rev sieve
printfn "Result = %A" (List.head sieve)