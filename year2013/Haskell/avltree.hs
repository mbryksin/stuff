data AVL a = N a (AVL a) (AVL a) Integer | E deriving (Show)

insert E val = N val E E 0
insert p@(N x l r h) val
	| val > x = balance $ N x l rtree (height l rtree)
	| val < x = balance $ N x ltree r (height ltree r)
	| otherwise = p
	where 
		rtree = insert r val
		ltree = insert l val
		height E E = 0
		height (N _ _ _ h') E = h' + 1
		height E (N _ _ _ h') = h' + 1
		height (N _ _ _ hl) (N _ _ _ hr) = max hl hr + 1

balance p@(N x l r h)
	| dx < 2 && dx > (-2) = p
	| dx == (-2) =
		case l of
		(N y xl xr hl) -> 
			case (delta xr xl) of
			(-1) -> (N y xl (N x xr r (hl-1)) hl)
			1 -> 
				case xr of
				(N z yl yr yh) -> (N z (N y xl yl yh) (N x yr r yh) (yh+1))
	| dx == 2 =
		case r of
		(N y xl xr hl) -> 
			case (delta xr xl) of
			1 -> (N y (N x l xl (hl-1)) xr hl)
			(-1) -> 
				case xl of 
				(N z yl yr yh) -> (N z (N x l yl yh) (N y yr xr yh) (yh+1))
	| otherwise = p
	where 
		delta a b = height a - height b 
		dx = height r - height l
		height E = 0
		height (N _ _ _ h') = h' + 1