
// by Matvey Bryksin
// the 1st of April
// projecteuler.net Problem 5

open System

let mutable result = 1
let N = 20

let SoE n = 
  let mutable sieve = [2..n]
  let sqrtn = Convert.ToInt32(Math.Sqrt (Convert.ToDouble n))
  let mutable i = 0;
  for i in [2..sqrtn] do
    sieve <- sieve |> List.filter (fun x -> (x <= i) || (x % i <> 0))
  sieve
let pow x N =
  let mutable i = x
  while (i < N) do
    i <- x * i
  i / x
for i in (SoE 20) do
  result <- result * (pow i N)
printfn "result = %A" result