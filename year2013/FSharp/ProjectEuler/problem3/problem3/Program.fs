
// by Matvey Bryksin
// the 2nd of April
// projecteuler.net Problem 3

open System

//let N = 600851475143L
//let N = 13195L
(*
let SoE n = 
  let mutable sieve = [2..n]
  let mutable i = 0
  for i in sieve do
    //printfn "...%A" i
    sieve <- sieve |> List.filter (fun x -> (x <= i) || (x % i <> 0))
  sieve

let n = Convert.ToInt32(Math.Sqrt (Convert.ToDouble N))
printfn "%A" n
let sieve = (SoE n)
let mutable max = 0
let mutable i = 0
for i in sieve do
  if N % (int64 i) = 0L then max <- i
  
printfn "result = %A" max

to sloooow
*)
let mutable lfactor = 600851475143L
let mutable f = true
let mutable i = 2L
while f do
  if lfactor <= i then f <- false else
    if lfactor % i = 0L then lfactor <- lfactor / i else i <- i + 1L
printfn "max = %A" lfactor