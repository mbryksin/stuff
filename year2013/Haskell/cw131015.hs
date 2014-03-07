{--
concat = foldl (++) []
listify x = map (:[]) x 

zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys
zipWith' _ _ _ = []

normalize [] = []
normalize (x:xs) = x : normalize [z | z<-xs, z /= x]

isProgression x = length x <= 2 || [y | _ <-z] == z where z@(y:_) = zipWith' (-) x (tail x)

isFunction r = length r == (length . normalize . (map fst)) r

isSymmetric r = sort r == sort [(y,x) | (x,y) <- r]

isReflexive = (< 0) . length

closure r = if length r == length r' then r else closure r' where
	r' = normalize (r ++ [(x, t) | (x,y) <- r, (z,t) <- r, y == z])

isTransitive x = x == closure x

-------
--isTransitive x = sort x == (sort . closure) x

-------

data Color = Red | Green | Blue
-- :i Color

colors = [Red, Green, Blue]

colorsString = map (\x -> case x of 
	       	       	       Red -> "Red"
			       Green -> "Green"
			       Blue -> "Blue"
		   ) colors
data Sound = Sound Int Int
--data Sound = Sound Int Sound | Stub

-- :i Sound

sounds = [Sound i j | i <- [1,2,3], j <- [4,5,6]]
_ = map (Sound 1) [3,4,5]

inRange (Sound a f) = f >= 20 && f <= 20000


data L a = Cons a (L a) | Nil
--a параметр

-- data List a = a ':' (L a) | []

len Nil = 0
len (Cons _ l) = len l + 1

--binary tree
--}

data BT a = N a (BT a) (BT a) | L

nnodes ( N _ l r ) = nnodes l + nnodes r + 1 
nnodes L = 0

nleaves L = 0
nleaves ( N _ L L ) = 1
nleaves ( N _ x y) = nleaves x + n leaves y

depth L = 0
depth (N _ x y) = depth x `max` depth y + 1

leaves = leaves' [] where
       leaves' acc l = acc
       leaves' acc (N x L L) = x:acc
       leaves' acc (N _ l r) = leaves' (leaves' acc l) r

nodes = nodes' [] where
      nodes' acc L = acc
      nodes' acc (N x l r) = nodes' (nodes' (x:acc) l) r

maxn (N n x y) = maxn' (maxn' n x) y where
     maxn' n L = n
     maxn' n (N m x y) = maxn' (maxn' ( n `max` m) x) y --протащить через x и y

--( N 2 (N 1 L L) (N 3 L L)) 

--сколько чисел меньше n и сколько больше
factor n L = (0,0)
factor n (N m l r) = (ll+lr+x, gel+ger+y) where
       (x, y) = if m < n then (1,0) else (0,1)
       (ll, gel) = factor n l
       (lr, ger) = factor n r