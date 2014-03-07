// by Matvey Bryksin
// the 18th of April
// struct of Binary Tree

open System
      
type BinTree =
  | Node of BinTree * int * BinTree
  | Empty

let rec isEmpty =
  function
  | Empty -> true
  | _ -> false
  
let mutable tree = Empty
let tree' = Node (Empty, 0, Empty)

if (isEmpty tree) &&
     not(isEmpty tree')
  then printfn "create tree : tests complited"
  else printfn "create tree : tests failed"

let rec insert x (tree:BinTree) =
  match tree with
  | Empty -> Node(Empty, x, Empty)
  | Node(left, value, right) when x < value -> Node(insert x left, value, right)
  | Node(left, value, right) when x > value -> Node(left, value, insert x right)
  | _ -> tree

tree <- insert 10 tree
if not(isEmpty tree)
  then printfn "insert tree : tests complited"
  else printfn "insert tree : tests failed"

let rec findElement x (tree:BinTree) = 
  match tree with
  | Empty -> false
  | Node(left, value, right) when x = value -> true
  | Node(left, value, right) when x < value -> findElement x left
  | Node(left, value, right) when x > value -> findElement x right
  | _ -> findElement x tree

tree <- insert 5 tree
tree <- insert 7 tree
tree <- insert 6 tree
tree <- insert 8 tree
tree <- insert 9 tree
tree <- insert 3 tree
tree <- insert 4 tree
tree <- insert 13 tree
tree <- insert 11 tree
tree <- insert 12 tree
tree <- insert 15 tree
tree <- insert 14 tree

if (findElement 12 tree) &&
     (findElement 5 tree) &&
       (findElement 7 tree) &&
         not(findElement 20 tree) &&
           not(findElement 1 tree) &&
             (findElement 15 tree)
  then printfn "find element : tests complited"
  else printfn "find element : tests failed"

let rec maxLeft tree =
  match tree with
  | Node(left, value, right) -> if left = Empty then Node(left, value, right) else maxLeft left
  | Empty -> Empty   
         
let rec removeElement x (tree:BinTree) =
  match tree with
  | Empty -> Empty
  | Node(left, value, right) when x < value -> Node(removeElement x left, value, right)
  | Node(left, value, right) when x > value -> Node(left, value, removeElement x right)
  | Node(Empty, value, Empty) when x = value -> Empty
  | Node(left, value, Empty) when x = value -> left
  | Node(Empty, value, right) when x = value -> right
  | Node(left, value, right) when x = value -> 
      let m = maxLeft right
      match m with
      | Node(left2, value2, right2) -> Node(left, value2, (removeElement value2 right))
      | Empty -> Empty
  | _ -> tree

tree <- removeElement 10 tree

if (findElement 11 tree) &&
     (findElement 5 tree) &&
       (findElement 12 tree) &&
         (findElement 15 tree) &&
           (findElement 7 tree) &&
             (findElement 3 tree) &&
               not(findElement 10 tree)
  then printfn "remove element : test complited"
  else printfn "remove element : test failed"

tree <- removeElement 5 tree
tree <- removeElement 7 tree

//print algo for russian Wiki
let printShift value = 
  for i in 1..value do printf " "

let mutable shift = 0
let rec printTree (tree:BinTree)=
  printShift shift
  match tree with
  | Node(Empty, value, Empty) -> 
      printfn "(%A nil nil)" value
      shift <- shift - 1
  | Node(left, value, right) ->
      printfn "(%A" value
      shift <- shift + 1
      printTree left
      shift <- shift + 1
      printTree right
      printShift shift
      printfn ")"
      shift <- shift - 1
  | Empty -> 
      printfn "nil"
      shift <- shift - 1  

printTree tree
