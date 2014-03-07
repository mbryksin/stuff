{-class Eq a where
	(==):: a->a->Bool
	(/=):: a->a->Bool
-}
--x == y
--x:a y: a Eq a
--f x y = x == y f:: Eq a(контекст) => a->a->Bool
{-
data T = T

instance Eq T where
	_ == _ = True
	_ /= _ = False

f s@T c@T = s == c
-}
{-
data T a = T a
--        ограничение
instance (Eq a, Num a) => Eq (T a) where
	(T x) == (T y) = x == (y + x)

class Eq a => Ord a where
	(<=) :: a->a->Bool
-}

{-
infixl 6 +++
infixl 7 ***

class SemiGroup a where
	(+++) :: a -> a -> a

class SemiGroup a => Monoid a where
	e :: a

class Monoid a => Group a where
	inv :: a -> a

class Group a => Ring a where
	(***) :: a -> a -> a

class Ring a => RingE a where
	eM :: a

class Ring a => Field a where
	invM :: a -> a

instance SemiGroup Int where
	x +++ y = x + y

instance Monoid Int where
	e = 0

instance Group Int where
	inv a = -a
-}
{-
data M a b = N a [b] (M a b) (M a b) Integer | E deriving (Show)

class Map (M a b) where
	empty :: M a b -> Bool
	insert :: Ord a => M a b -> a -> b -> M a b
	find :: Ord a => M a b -> a -> Maybe b
	remove :: Ord a => M a b -> a -> M a b
	fold :: (a -> b -> c -> c) -> M a b -> c -> c

instance Map (M a b) where
	empty E = True
	empty _ = False

-}
--*->(*->*)->*
--data A a b = S (b a)
--A Int []


--data T a b = ...
class Ord a => Map m a b where
	empty :: m a b
--kind m:: *->*->*

instance Ord a => Map T a b where

