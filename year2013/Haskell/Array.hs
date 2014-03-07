--lenghtA :: A a -> Int
--getA :: A a -> Int -> a
--putA :: A a -> Int -> a -> A a
--subA :: A a -> Int -> Int -> A a
--mapA :: (a->b) -> A a -> A b
--foldA :: (a->b->b) -> A a -> b -> b


data A x = A Int (Int -> x) deriving (Show)

class Array a where
	lenghtA :: a x -> Int
	getA :: a x -> Int -> x
	putA 

instance Array A where
	lenghtA (A n _) = n
	getA (A _ f) = f
	putA (A n f) i x = A n (\ j -> if j == i then x else f j)
