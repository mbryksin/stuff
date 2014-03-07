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
many a = a ||> (\x -> many a ||> val . (x:)) ||| val []

opt :: Parser a -> Parser (Maybe a)
opt a = a ||> val . Just ||| val Nothing

data E = 
	X String | 
	N Integer | 
	Mul E E | 
	Div E E | 
	Add E E | 
	Sub E E | 
	Eq E E | 
	Ls E E | 
	LsOE E E | 
	Gt E E | 
	GtOE E E | 
	And E E | 
	Or E E deriving Show

eof :: [(a,String)] -> [a]
eof = map fst.filter ((==[]) . snd)

empty :: Parser a
empty _ = []

oneOf = foldl (\acc b -> acc ||| sym b) empty

letter = oneOf "abcd..._"
digit = oneOf "0123456789"

ident = letter ||> (\x -> many (letter ||| digit) ||> (\xs -> val $ X (x:xs)))

literal = digit ||> (\x -> many digit ||> (\xs -> val $ N $ read(x:xs)))

primary =
	ident |||
	literal |||
	sym '(' ||> (\_ -> expr ||>(\e -> sym ')' ||> (\_->val e)))

multi =
	primary ||> (\x -> op ||> (\o -> multi ||> (\y -> val $ x `o` y) )) ||| primary
	where
		op = sym '*' ||> (\_ -> val Mul) |||
			 sym '/' ||> (\_ -> val Div)

addi =
	multi ||> (\x -> op ||> (\o -> addi ||> (\y -> val $ x `o` y))) ||| multi
	where
		op = sym '+' ||> (\_ -> val Add) |||
			 sym '-' ||> (\_ -> val Sub)

booli =
	addi ||> (\x -> op ||> (\o -> addi ||> (\y -> val $ x `o` y))) ||| addi
	where
		op = sym '=' ||> (\_ -> val Eq) |||
			 sym '<' ||> (\_ -> val Ls) |||
			 sym '<' ||> (\_ -> sym '=' ||> (\_ -> val LsOE)) |||
			 sym '>' ||> (\_ -> val Gt) |||
			 sym '>' ||> (\_ -> sym '=' ||> (\_ -> val GtOE))

-- sym '>' ||> (\_ -> opt (sym '=') ||> choose Gt Ge)
--choose a b Nothing = val a choose a b (Just _) = val b

logi =
	booli ||> (\x -> op ||> (\o -> logi ||> (\y -> val $ x `o` y))) ||| booli
	where
		op = sym '&' ||> (\_ -> val And) |||
			 sym '|' ||> (\_ -> val Or)


expr = logi

--eof $ expr "1"
--eof $ expr "abc1"
--eof $ expr "(1)"
{-
ident: letter (letter |digit)*
literal: digit digit*
primary: ident|literal|'('expression')'

multi: primary ('*'|'/') multi | primary
addi : multi ('+'|'-') addi | addi

> >= < <= = \=
expr: primary
-}

{-
борьба с ассоциативностью
multi : primary op multi | primary
a/(b/c)
список праймэри длиной 1 или больше
primary (op primary)* -> список пар -> foldl
		   ||>

независимо от 1

переиспользовать
-}
{-addi: primary op addi | primary
a - b - c - d
(a -) (b -) (c -) d

протаскивать параметром

addi c = primary (a) op (p) addi () | c primary
c - затыкание дырки
c:: дерево для  операнда -> дерево с закрытой дыркой


-}

mult = multi (\x -> x) 
	where 
	multi c = primary ||> (\a -> op ||> (\o -> multi (\place -> (c a) `o` place))) ||| 
			  primary ||> (\a -> val $ c a)
				where op = sym '*' ||> (\_ -> val Mul) |||
					       sym '/' ||> (\_ -> val Div)

add = addi (\x -> x)
	where
	addi c = multi ||> (\a -> op ||> (\o -> addi (\place -> (c a) `o` place))) ||| 
			 multi ||> (\a -> val $ c a)
				where
					op = sym '+' ||> (\_ -> val Add) |||
			 			 sym '-' ||> (\_ -> val Sub)
--генератор парсера для выражений
-- expr p(парсер простейших праймэри) список ассоциативностей и выражений, по увеличению приоритета 
--[[слабые операции],...[сильные операции]]
--([op1,op2,op3],Right/Left/None)


--expr primary [([sym '&' ||> (\_ -> val And), sym '|' ||> (\_ -> val Or)], Right), ([sym....], None), ]
--reli не ассоциативная операция
