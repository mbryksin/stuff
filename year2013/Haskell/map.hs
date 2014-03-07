data Map a b = N a [b] (Map a b) (Map a b) Integer | E deriving (Show)

-----------------------------------
make a b l r = N a b l r ((max (h l) (h r)) + 1)
h E = 0
h (N _ _ _ _ n) = n

balance n@(N a b l r k) =
	if h l > h r + 1 then rotR a b l r else 
	if h r > h l + 1 then rotL a b l r else n
	where
		rotL a b z (N c f d e _) 
			| h d > h e = rotL a b z (rotR c f d e)
			| otherwise = make c f (make a b z d) e
		rotR a b (N c f d e _) z
			| h d < h e = rotR a b (rotL c f d e) z
			| otherwise = make c f d (make a b e z)

-----------------------------------
empty :: Map a b -> Bool
empty E = True
empty _ = False

insert :: Ord a => Map a b -> a -> b -> Map a b
insert E a b = N a [b] E E 1
insert (N a b l r k) x y
	| x < a = let l' = insert l x y in balance $ make a b l' r
	| x > a = let r' = insert r x y in balance $ make a b l r'
	| otherwise = N a (y:b) l r k

find :: Ord a => Map a b -> a -> Maybe b
find E _ = Nothing
find (N a (b:bs) l r h) x
	| x < a = find l x
	| x > a = find r x
	| otherwise = Just b

remove :: Ord a => Map a b -> a -> Map a b
remove m@(N a b l r k) a' = case find m a' of
	Nothing -> m
	Just _ ->
		if a' > a then balance $ make a b l (remove r a') else
		if a' < a then balance $ make a b (remove l a') r else 
		case b of
			[y] -> case r of
				E -> l
				_ -> let (i,j,g) = findl r in balance $ make i j l g
				where 
					findl (N ar br E rr _ ) = (ar, br, rr)
					findl (N ar br lr rr _) = let (ar', br', lr') = findl lr in (ar', br', balance $ make ar br lr' rr)
			y:ys -> (N a ys l r k)

fold :: (a -> b -> c -> c) -> Map a b -> c -> c
fold f E acc = acc
fold f (N a (b:bs) l r k) acc = fold f r $ fold f l (f a b acc)