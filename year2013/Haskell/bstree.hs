data BT a = N a (BT a) (BT a) | L deriving (Show)

-- 1st task
insert L val = N val L L
insert p@(N x l r) val
	| val > x = N x l (insert r val)
	| val < x = N x (insert l val) r 
	| otherwise = p
-- 2nd task
find L _ = Nothing
find p@(N x l r) val
	| val == x = Just p
	| val < x = find l val
	| otherwise = find r val

-- 3rd task
isBST t@(N x l r) = fst $ isBST' t where
		isBST' L = (True, [])
		isBST' (N x l r) = (bl (isBST' l) (isBST' r)) where
				bl (x1,y1) (x2,y2) = (x1 && x2 && (filter (>=x) y1) == [] && (filter (<=x) y2) == [], y1++[x]++y2)

isBST2 t@(N x l r) = raise $ treesort t where
	raise l = r' l (-1000) where
		r' [] _ = True
		r' (x:xs) acc = (x > acc) && (r' xs x)
-- 4th task
treesort L = []
treesort (N x l r) = treesort l ++ [x] ++ treesort r
