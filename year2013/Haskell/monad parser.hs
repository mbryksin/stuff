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
	   | Plus E 
	   | Minus E 
	   | Mul E E 
	   | Div E E 
	   | Add E E 
	   | Sub E E 
	   | Eq E E 
	   | NEq E E
	   | Ls E E 
	   | LsOE E E 
	   | Gt E E 
	   | GtOE E E 
		   | And E E 
	   | Or E E 
	   deriving Show

oneOf = foldl (\a b -> a ||| sym b) empty
letter = oneOf "_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
digit = oneOf "0123456789"

literal = do x <- digit
             xs <- many digit
             return $ N $ read (x:xs)

symone op node = do sym op
                    return node

symtwo op1 op2 node = do sym op1 
                         sym op2 
                         return node

primary =
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

multi = left primary op
	    where op = symone '*' Mul ||| symone '/' Div

addi = left multi op
	   where op = symone '+' Add ||| symone '-' Sub

binary p1 p2 op = p1 |||
                  do x <- p1
                     o <- op
                     y <- p2
                     return $ x `o` y

booli = binary addi addi op
	where op = symone '=' Eq |||
			   symone '<' Ls |||
			   symone '>' Gt |||
			   symtwo '<' '=' LsOE |||
			   symtwo '>' '=' GtOE |||
			   symtwo '<' '>' NEq

logi = binary booli logi op
	where op = symone '&' And |||
			   symone '|' Or

expr = logi 
parse = eof . apply (expr)

