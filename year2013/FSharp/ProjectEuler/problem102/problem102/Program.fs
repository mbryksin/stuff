// by Matvey Bryksin
// the 13th of May
// projecteuler.net Problem 102 ( < 10000 )

open System
open System.IO

let StrToList str = //parsing string to List
  let length = (String.length str) - 1
  let mutable negative = 0
  let mutable list = []
  let mutable x = 0
  for i in 0..length do
    if (str.[i] = '-')
      then negative <- 1
      else if (str.[i] = ',')
             then
               if (negative = 1)
                 then x <- x * (-1)
               list <- List.append list [x]
               x <- 0
               negative <- 0
             else
               x <- x * 10 + int str.[i]
               if (i = length)
               then
                 if (negative = 1)
                 then x <- x * (-1)
                 list <- List.append list [x]
                 x <- 0
                 negative <- 0
  list

let BeamCross s x1 y1 x2 y2 =
  if (s >= 0.0) && (s <= 1.0)
    then
      let t1 = x1 + s * (x2 - x1) //checking beam, but not straight
      let t2 = y1 + s * (y2 - y1) //t1 = t2, but smth may be wrong
      if (t1 > 0.0) && (t2 > 0.0)
        then 1
        else 0
    else 0

let calcS x1 y1 x2 y2 =
  (x1 - y1) / (y2 - x2 + x1 - y1) //handmade formula
      
let TriangleContains (list:int list) =
  let (xa, ya) = ((float)list.[0], (float)list.[1])
  let (xb, yb) = ((float)list.[2], (float)list.[3])
  let (xc, yc) = ((float)list.[4], (float)list.[5])
  let Sab = calcS xa ya xb yb
  let Sbc = calcS xb yb xc yc
  let Sac = calcS xa ya xc yc
  let numCross = (BeamCross Sab xa ya xb yb) + (BeamCross Sbc xb yb xc yc) + (BeamCross Sac xa ya xc yc)
    (*finding sum of beam's crossing triangle*)
  numCross % 2

let rec iter list =
  match list with
  | [] -> 0
  | h :: t ->
    let list' = (StrToList h)
    iter t + TriangleContains list'

let text = File.ReadAllLines(@"/home/matthew/GitHub/repo71group/FSharp/ProjectEuler/problem102/triangles.txt");
let lines = text |> Array.toList
printfn "Result = %A" <| iter lines
