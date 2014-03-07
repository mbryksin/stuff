--data AVL a h = N a (AVL a h) (AVL a h) h | E deriving (Show)
--data M a b = AVL (a,b) h

data T a = N Integer a (T a) (T a) | L deriving (Show)

insert L x = N 1 x L L
insert n@(N k a l r) x
	| x < a = let l' = insert l x in
				if h l' > h r + 1 then rotR a l' r else make a l' r
	| x > a = let r' = insert r x in
				if h r' > h l + 1 then rotL a l r' else make a l r'
	| otherwise = n
	where 
		rotL a b (N _ c d e) 
			| h d > h e = rotL a b (rotR c d e)
			| otherwise = make c (make a b d) e
		rotR a (N _ c d e) b
			| h d < h e = rotR a (rotL c d e) b
			| otherwise = make c d (make a e b)
		h L = 0
		h (N n _ _ _) = n
		make a l r = N ((max (h l) (h r)) + 1) a l r
