{-
data Actor = String
data State = Here
              {
                this :: [Actor],
                that :: [Actor]
              }
            | There
              {
                this :: [Actor],
                that :: [Actor]
              }

rule ("Wolf","Goat") = False
rule ("Goat","Wolf") = False
rule ("Goat","Cabbage") = False
rule ("Cabbage","Goat") = False
rule _ = True

carry = move ["Wolf", "Goat", "Cabbage"] [] 
	move this that = foldl (\x -> if rule (delete x this) && (rule (x:that)) then ) 

-}

--2

data D = A | T | G | C deriving (Show)
change A = T
change T = A
change G = C
change C = G

getlist (x:xs) = change x:getlist xs
getlist []     = []

--3
{-
fun A _ _ = Just 0
fun _ _ _ = Nothing
parsing [A,T,C,T,T,A,G,C] fun
[0,0]
-}

parsing [] _ = []
parsing (a:[]) _ = []
parsing (a:b:[]) _ = []
parsing (a:b:c:xs) f =
	case (f a b c) of
		Nothing -> parsing (b:c:xs) f
		Just x -> x:parsing xs f

--4
{-
fun 5 = Just (A,T,T)
fun 4 = Just (G,C,C)
fun _ = Nothing
reparsing [22,2,2,5,2,3,4] fun
[A,T,T,G,C,C]
-}
reparsing [] _ = []
reparsing (n:ns) f =
	case (f n) of
		Nothing 	 -> reparsing ns f
		Just (a,b,c) -> a:b:c:reparsing ns f		 
