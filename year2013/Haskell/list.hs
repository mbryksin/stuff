--list

mylength [] = 0
mylength (x:xs) = 1 + mylength xs

myconcat [] a = a
myconcat (x:xs) a = x:(myconcat xs a)

myreverse [] = []
myreverse (x:xs) = (myreverse xs) ++ [x]

mytake 0 _ = []
mytake _ [] = []
mytake n (x:xs) = x:(mytake (n-1) xs)

myconcatlist [] = []
myconcatlist (x:xs) = x ++ (concat xs)

infixl 6 ***
[] *** p@(x:xs) = []
p@(x:xs) *** [] = []
(x:xs) *** p2@(y:ys) =
      (f p2) ++ (xs *** p2) where
      	 f [] = []
	 f p2@(y:ys) = (x * y):(f ys)