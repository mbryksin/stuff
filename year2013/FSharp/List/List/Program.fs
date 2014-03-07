// by Matvey Bryksin
// the last commit at the 13th of May in 2013
// List's functions

open System

let rec addToEnd list x =
  match list with
  | [] -> x::[]
  | head::tail -> head::(addToEnd tail x)

if addToEnd [1;2;3] 4 = [1;2;3;4] &&
     addToEnd [2;3;4;5;6] 1 = [2;3;4;5;6;1] &&
       addToEnd [-1;0;1] 10 = [-1;0;1;10] &&
         addToEnd [8] 2 = [8;2] &&
           addToEnd [] 100 = [100]
             then printfn "addToEnd: tests completed"
             else printfn "addToEnd: tests failed"
//-------
let rec append list1 list2 =
  match list1 with
  | head::tail -> head::(append tail list2)
  | [] ->
    match list2 with
    | head::tail -> head::(append [] tail)
    | [] -> []

if append [] [] = [] &&
     append [1] [2;3;4;5;6] = [1;2;3;4;5;6] &&
       append [-1;0;1] [2;3;4] = [-1;0;1;2;3;4] &&
         append [8;9;10] [] = [8;9;10] &&
           append [] [1;2;3;4] = [1;2;3;4]
             then printfn "append: tests completed"
             else printfn "append: tests failed"
//-------
// reverse O(n)
let reverse list =
  let rec reverse2 temp list =
    match temp with
    | [] -> list
    | head::tail -> reverse2 (tail) (head::list)
  (reverse2 list [])

if reverse [1;2;3] = [3;2;1] &&
     reverse [] = [] &&
       reverse [1] = [1] &&
         reverse [1;2;3;4;5;6;7] = [7;6;5;4;3;2;1]
             then printfn "reverse: tests completed"
             else printfn "reverse: tests failed"
//-------
let rec find list element =
  match list with
  | [] -> false
  | head::tail -> if head = element then true else (find tail element)

if find [1;2;3;4] 5 = false &&
      find [1;2;3;4] 3 &&
       find [] 3 = false &&
         find [1;2;3;4;5;6;7] 7
             then printfn "find: tests completed"
             else printfn "find: tests failed"
//-------
(*
let rec map list f =
  match list with
  | head::tail -> (f head)::(map tail f)
  | [] -> []
*)

let map list func = 
  List.foldBack (fun x tail -> (func x)::tail) list []
  
if map [1;2;3;4;5] (fun x -> x + 10) = [11;12;13;14;15] &&
     map [0;1;2;3;4] (fun x -> x % 2) = [0;1;0;1;0] &&
       map [0;1;2;3;4] (fun x -> x * x) = [0;1;4;9;16] &&
         map [1;2;3;4;5] (fun x -> 0) = [0;0;0;0;0]
             then printfn "map: tests completed"
             else printfn "map: tests failed"
