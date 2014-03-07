type Parser a = String -> [(a, String)]

sym :: Char -> Parser Char
sym a (x:xs) | a == x = [(a, xs)]
sym _ _ = []

val :: a -> Parser a
val a s = [(a, s)]

infixl 2 |||
p1 ||| p2 = \s -> (p1 s) ++ (p2 s)

infixl 3 ||>
p1 ||> p2 = \s -> concat [p2 a s | (a,s) <- p1 s]

many:: Parser a -> Parser [a]
many p = p ||> (\x -> many p ||> val . (x:)) ||| val []

opt :: Parser a -> Parser (Maybe a)
opt a = a ||> val . Just ||| val Nothing

eof :: [(a,String)] -> [a]
eof = map fst.filter ((==[]) . snd)

empty :: Parser a
empty _ = []

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
ident = letter ||> (\x -> many (letter ||| digit) ||> (\xs -> val $ X (x:xs)))
literal = digit ||> (\x -> many digit ||> (\xs -> val $ N $ read(x:xs)))

symone op node = sym op ||> (\_ -> val node)
symtwo op1 op2 node = sym op1 ||> (\_ -> (sym op2 ||> (\_ -> val node)))

primary =
	ident |||
	literal |||
	sym '(' ||> (\_ -> expr ||> (\e -> symone ')' e))

--pp*
left p op = p ||> (\x -> many star ||> (\xs -> val $ foldl (\acc (o, y) -> acc `o` y) x xs) )
	where star = op ||> (\o -> p ||> (\y -> val $ (o, y)))

multi = left primary op
	where op = symone '*' Mul ||| symone '/' Div

addi = left multi op
	where op = symone '+' Add ||| symone '-' Sub

binary p1 p2 op = p1 ||> (\x -> op ||> (\o -> p2 ||> (\y -> val $ x `o` y))) ||| p1

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
pars = eof . expr