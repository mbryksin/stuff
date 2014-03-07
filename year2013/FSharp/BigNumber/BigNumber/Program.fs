// by Matvey Bryksin
// the 20th of May
// description of class BigNumber

open System

type BigNumber(init:string) =
  let len = 4
  let osn = 10000
  let mutable amount = if init.Length % len = 0 then init.Length / len else init.Length / len + 1
  let mutable sign = init.StartsWith("-");

  let mutable digits =
    [|let i = ref(init.Length-1)
      while !i>=0 do
        yield Math.Abs(int (init.Substring ((if !i-len+1 < 0 then 0 else !i-len+1), (if !i-len+1 < 0 then !i+1 else len)))); i:=!i - len|]
  
  override this.ToString() = (if sign && this.DigitsArray <> [|0|] then "+" else "") + (this.ArrayToString)  
  
  member private this.ArrayToString =
    let mutable str = ""
    let mutable zero = ""
    for i = this.DigitsArray.Length - 1 downto 0 do
      if (i <> this.DigitsArray.Length - 1)
        then 
          for j = 1 to len - (string digits.[i]).Length do zero <- zero + "0"
      str <- str + zero + string digits.[i]
      zero <- ""   
    str  
  
  member this.Abs =
    let res = new BigNumber(this.ArrayToString)
    res.Sign <- false
    res.Amount <- this.Amount
    res

  member this.Print =
    printfn "%s" <| this.ArrayToString
  
  override this.Equals(that) =
    match that with
    | :? BigNumber as x -> this.isSimilar(x) 
    | :? int as n -> this.isSimilar(new BigNumber(n))
    | :? string as str -> this.isSimilar(new BigNumber(str))
    | _ -> failwith "uncomparable"
  
  override this.GetHashCode() =
    this.ArrayToString.GetHashCode()
  
  member private left.isSimilar(right: BigNumber) =
    left.Sign = right.Sign 
      && left.Amount = right.Amount 
        && ( List.sum [for i in [0..left.Amount-1] do yield if left.Digits(i) = right.Digits(i) then 0 else 1] ) = 0      
  
  member this.CompareTo(that) =
    (this :> IComparable).CompareTo(that)

  member private this.cmp(that: BigNumber) =
    let rec getdiff l =
      match l with
      | hd::tl when hd = 0 -> getdiff tl
      | hd::tl when hd > 0 -> 1
      | hd::tl when hd < 0 -> -1
      | [] -> 0
      | _ -> failwith "error"         

    let mutable res = 0
    if this.Sign && (not that.Sign) then res <- -1 else
      if (not this.Sign) && that.Sign then res <- 1 else
        if (this.Sign = that.Sign)
          then
            if this.Amount > that.Amount
              then if this.Sign then res <- -1 else res <- 1
              else
                if this.Amount < that.Amount
                  then if this.Sign then res <- 1 else res <- -1
                  else
                    let listdiff = [ for i = this.Amount-1 downto 0 do yield this.Digits(i) - that.Digits(i)]
                    res <- (getdiff listdiff)            
    res                                      
                                                                                                              
  interface System.IComparable with 
    member this.CompareTo(that) =
      match that with
      | :? BigNumber as n -> this.cmp(n)
      | :? int as x -> this.cmp(new BigNumber(x))
      | :? string as s -> this.cmp(new BigNumber(s))
      |_ -> failwith "can't compare"
  
  member private left.AddAbs(right: int) =
    left.AddAbs(new BigNumber(right))
  
  member private left.AddAbs(right: BigNumber) = 
    let res = new BigNumber("")
    res.Amount <- Math.Max (int left.Amount, int right.Amount)
    let array = [|let r = ref 0
                  for i in [0..res.Amount] do
                    if i = res.Amount
                      then 
                        if !r = 1 then yield 1; res.Amount <- res.Amount + 1
                      else
                        if left.Amount > i
                          then 
                            if right.Amount > i
                              then
                                yield (left.Digits(i) + right.Digits(i) + !r) % osn; 
                                r := (left.Digits(i) + right.Digits(i) + !r) / osn
                              else
                                yield (left.Digits(i)+ !r) % osn; 
                                r := (left.Digits(i)+ !r) / osn
                          else
                            if right.Amount > i
                              then 
                                yield (right.Digits(i) + !r) % osn; 
                                r := (right.Digits(i) + !r) / osn|]
    res.DigitsArray <- array
    res   
  
  member left.Add(right:obj) =
    match right with
    | :? BigNumber as x -> if left.Sign = x.Sign 
                             then 
                               if left.Sign 
                                 then (left.Abs.AddAbs(x.Abs)).ToNegative
                                 else left.AddAbs(x)
                             else left.Abs.Sub(x.Abs) 
    | :? int as n -> if ((not left.Sign) && n > 0) || (left.Sign && n < 0)
                       then 
                         if left.Sign
                           then (left.Abs.AddAbs(Math.Abs n)).ToNegative
                           else left.AddAbs(n)
                       else left.Abs.Sub(Math.Abs n)
    | _ -> failwith "unknown error"
  
  member private this.ChangeSign =
    let res = new BigNumber(this.ArrayToString)
    res.Sign <- not this.Sign
    res.Amount <- this.Amount
    res 
  
  member this.ToNegative =
    let res = new BigNumber(this.ArrayToString)
    res.Sign <- true
    res.Amount <- this.Amount
    res
  
  member left.Sub(right:obj) =
    match right with
    | :? BigNumber as x ->
      match (left.CompareTo(0), x.CompareTo(0)) with
      | (-1, 1) -> left.AddAbs(x).ToNegative
      | (1, 1) -> 
        if left.CompareTo(x) <> -1 
          then left.SubAbs(x) 
          else x.SubAbs(left).ToNegative
      | (1, -1) -> left.AddAbs(x.Abs)
      | (-1, -1) -> x.Abs.Sub(left.Abs)
      | (0, _) -> x.ChangeSign
      | (_, 0) -> left
      | _ -> failwith "unknown error"
    | :? int as n -> left.Sub(new BigNumber(n))
    | _ -> failwith "unknown error"    
  
  member private left.SubAbs(right: int) =
    left.SubAbs(new BigNumber(right))
      
  member private this.SubAbs(that: BigNumber) =
    let res = new BigNumber(this.ArrayToString)
    res.Amount <- this.Amount
    let r = ref 0
    let array = [|for i in [0..this.Amount-1] do
                    if i <= that.Amount - 1
                     then
                       let x = res.Digits(i) - that.Digits(i) + !r
                       if x < 0
                         then yield x + osn; r := -1
                         else yield x; r := 0
                     else
                       let x = res.Digits(i) + !r
                       if x < 0
                         then yield x + osn; r := -1
                         else yield x; r := 0 |]
    
    let rec superfilter l =
      match l with
      | hd::tl when hd = 0 -> superfilter tl
      | hd::tl when hd <> 0 -> hd::tl
      | [] -> [0]
      | _ -> failwith "unknown error"                       
    res.DigitsArray <- Array.rev <| List.toArray (superfilter <| Array.toList (Array.rev array))
    let amount = if res.ArrayToString.Length % len = 0 then res.ArrayToString.Length / len else res.ArrayToString.Length / len + 1
    res.Amount <- amount
    res
  
  member left.Mult(right: obj) =
    match right with
    | :? BigNumber as x -> 
      if left.Sign = x.Sign 
        then left.MultAbs(x) 
        else left.MultAbs(x).ToNegative
    | :? int as n ->
      if (left.Sign && n < 0) || ((not left.Sign) && n > 0)
        then left.MultAbs(n)
        else left.MultAbs(n).ToNegative
          
    | :? string as str -> left.Mult(new BigNumber(str))
    | _ -> failwith "unknown error"

  member private left.MultShift (right: int) (shift: int) =
    let res = new BigNumber("")
    res.Amount <- left.Amount + shift
    let r = ref 0
    let array = [|for i in [1..shift] do yield 0
                  for i in [0..left.Amount] do
                    if i = left.Amount
                     then
                       if !r <> 0 then yield !r; res.Amount <- res.Amount + 1
                     else
                       let x = left.Digits(i) * right + !r
                       //let (d',r') = Math.DivRem(x, osn)
                       r := x / osn
                       yield (x - !r * osn)|]            
    res.DigitsArray <- array
    res   
  
  member left.MultAbs(right: int) =
    let res = left.MultShift right 0
    res
  
  member left.MultAbs(right: BigNumber):BigNumber = 
    let bigArray = [| for i = 0 to right.Amount-1 do yield (left.MultShift (right.Digits(i)) i) |]
    let mutable x = bigArray.[0]
    for i in [1.. right.Amount-1] do
      x <- x.AddAbs(bigArray.[i])
    x
  
  
  
  member this.Sign with get() = sign and set value = sign <- value
  member this.Amount with get() = amount and set value = amount <- value

  member this.Digits with get(index) = digits.[index] and set index value = digits.[index] <- value
  member this.DigitsArray with private get() = digits and private set value = digits <- value
  
  new(n:int) = BigNumber(string n)

//tests

let p = new BigNumber("100500")
let q = new BigNumber("1234567")
let o = new BigNumber("99999999")
let y = new BigNumber("78123410000001")
let h = new BigNumber("8072603837415432")
let r = new BigNumber("9999999999999998765412345643")
let g = new BigNumber("9999999999432345765412347654")
let p' = new BigNumber(-1234567)
let q' = new BigNumber(-543678)
let o' = new BigNumber("-100000001")
let y' = new BigNumber("-763956476826597456321")
let h' = new BigNumber("-15474556364765583")


if y.Add(o).Equals "78123510000000" 
     && o.Add(h).Equals "8072603937415431" 
       && h.Add(y).Equals "8150727247415433"
         && q.Add(100500).Equals "1335067"
           && r.Add(g).Equals "19999999999432344530824693297"
             && h.Add(y').Equals "-763948404222760040889" 
               && h'.Add(y').Equals "-763971951382962221904"
  then printfn "Add: everything is ok"
  else printfn "Add: error"

if h.Mult(1072).Equals "8653831313709343104"
     && y.Mult(h).Equals "630659339357987207066957415432"
       && p.Mult(q).Equals "124073983500"
         && p.Mult(10).Equals 1005000
           && h'.Mult(o').Equals "1547455651951114664765583"
             && h.Mult(h').Equals "-124919963092508042831069266676856"
  then printfn "Mult: everything is ok"
  else printfn "Mult: error"

  
if h.Sub(y).Equals "7994480427415431" 
     && h.Sub(o).Equals "8072603737415433"
       && r.Sub(g).Equals "567652999999997989"
         && g.Sub(g).Equals 0
           && y'.Sub(r).Equals "-10000000763956475592009801964"
             && h'.Sub(o').Equals "-15474556264765582"
               && h.Sub(h').Equals "23547160202181015"
   then printfn "Sub: everything is ok"
   else printfn "Sub: error"   
