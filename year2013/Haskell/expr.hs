newtype Parser a = P(String -> [(a, String)])

empty :: Parser a
empty = P (\_ -> [])

val :: a -> Parser a
val a = P (\s -> [(a, s)])

sym :: Char -> Parser Char
sym a = P p where p (x:xs) | a == x = [(a, xs)]
                  p _               = []

infixl 2 |||
(P p1) ||| (P p2) = P(\s -> p1 s ++ p2 s)

apply (P p) s = p s

infixl 3 ||>
(P p1) ||> p2 = P ( \s -> concat [apply (p2 a) s | (a,s) <- p1 s] )

instance Monad Parser where
	return = val
	(>>=) = (||>)

many:: Parser a -> Parser [a]
many p = return [] |||
         do x  <- p
            xs <- many p
            return (x:xs)

opt :: Parser a -> Parser (Maybe a)
opt a = return Nothing |||
        do x <- a
           return (Just x)

eof :: [(a,String)] -> [a]
eof = map fst.filter ((==[]) . snd)

data E = X String 
	   | N Integer
	   | Pow E Integer
	   | Mul E E 
	   | Div E E 
	   | Add E E 
	   | Sub E E

oneOf = foldl (\a b -> a ||| sym b) empty
letter = oneOf "_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"          
digit = oneOf "0123456789"

ident = do x <- letter 
           xs <- many (letter ||| digit) 
           return $ X (x:xs)

literal = do x <- digit
             xs <- many digit
             return $ N $ read (x:xs)

symone op node = do sym op
                    return node

primary =
	ident |||
	literal |||
	do sym '(' 
	   e <- expr 
	   symone ')' e

--rule aa*
left p op = do x <- p
               xs <- many star
               return $ foldl (\acc (o, y) -> acc `o` y) x xs
            where star = do o <- op 
                            y <- p 
                            return $ (o, y)

powi = ex ||| primary
       where ex = do x <- primary
                     sym '^'
                     (N y) <- literal
                     return $ Pow x y

multi = left powi op
	    where op = symone '*' Mul ||| symone '/' Div

addi = left multi op
	   where op = symone '+' Add ||| symone '-' Sub

expr = addi
parse = head . eof . apply (expr)

--derivation
derivation (N _) x = N 0
derivation (X s) x | x == s    = N 1
                   | otherwise = N 0
derivation (Add first second) x = Add (derivation first x) (derivation second x)
derivation (Sub first second) x = Sub (derivation first x) (derivation second x)
derivation (Mul first second) x = Add (Mul (derivation first x) second) (Mul first (derivation second x))
derivation (Div first second) x = Div
                                    (Sub
                                        (Mul (derivation first x) second)
                                             (Mul first (derivation second x)))
                                        (Pow second 2)
derivation (Pow base power) x = if power == 0
                                       then N 0
                                       else Mul (N power) (Mul (Pow base (power-1)) (derivation base x))
--

d str x  = reduce (derivation (parse str) x)

--reduce
reduceHelper (Add (N a) (N b)) = N (a + b)
reduceHelper (Add first (N 0)) = first
reduceHelper (Add (N 0) second) = second

reduceHelper (Mul (N a) (N b)) = N (a * b)
reduceHelper (Mul (N 1) second) = second
reduceHelper (Mul first (N 1)) = first
reduceHelper (Mul (N 0) _) = N 0
reduceHelper (Mul _ (N 0)) = N 0

reduceHelper (Sub (N a) (N b)) = N (a - b)
reduceHelper (Sub first (N 0)) = first
reduceHelper (Sub first (N x)) | x < 0 = Add first (N (-x))


reduceHelper (Div (N a) (N b)) = Div (N (div a g)) (N (div b g))
                                 where g = gcd a b
reduceHelper (Div first (N 1)) = first

reduceHelper (Pow _ 0) = N 1
reduceHelper (Pow base 1) = base
reduceHelper (Pow (N 0) _) = N 0
reduceHelper (Pow (N x) p) = N (x^p)



{-
reduceHelper (Add (X a) (X b)) | a == b = Mul (N 2) (X a)
reduceHelper (Add (Mul (N a) (X b)) (Mul (N c) (X d))) | b == d = Mul (N (a + c)) (X b)
reduceHelper (Sub (Mul (N a) (X b)) (Mul (N c) (X d))) | b == d = Mul (N (a - c)) (X b)
-}

reduceHelper other = other

reduce (Add first second) = reduceHelper (Add (reduce first) (reduce second))
reduce (Sub first second) = reduceHelper (Sub (reduce first) (reduce second))
reduce (Mul first second) = reduceHelper (Mul (reduce first) (reduce second))
reduce (Div first second) = reduceHelper (Div (reduce first) (reduce second))
reduce (Pow base pow)     = reduceHelper (Pow (reduce base) pow)
reduce other              = other

f = reduce . parse
--end reduce

{-
openBrackets (Mul x (Add l r)) = Add (openBrackets (Mul x l)) (openBrackets(Mul x r)) 
openBrackets (Mul (Add l r) x) = Add (openBrackets (Mul l x)) (openBrackets(Mul r x))
openBrackets (Mul x (Sub l r)) = Sub (Mul x l) (Mul x r) 
openBrackets (Mul (Sub l r) x) = Sub (Mul l x) (Mul r x)
-}

showInBrackets x = '(':(show x) ++ ")"
instance Show E where
    show (N x) = show x
    show (X a) = show a
    show (Add x y) = show x ++ "+" ++ show y
    show (Sub x y) = show x ++ "-" ++ showSubtract y
                     where showSubtract x@(Add _ _) = showInBrackets x
                           showSubtract x@(Sub _ _) = showInBrackets x
                           showSubtract x = show x
    show (Mul x y) = showMulty x ++ "*" ++ showMulty y
                     where showMulty x@(Add _ _) = showInBrackets x
                           showMulty x@(Sub _ _) = showInBrackets x
                           showMulty x = show x
    show (Div x y) = showDivide x ++ "/" ++ showDivide y
                     where showDivide (X a) = show a
                           showDivide (N x) = show x
                           showDivide x@(Pow _ _) = show x
                           showDivide x = showInBrackets x
    show (Pow base power) = (showBase base) ++ '^':(show power)
                            where showBase (N x) = show x
                                  showBase x = showInBrackets x

