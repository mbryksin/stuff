fromFun _ [] = []
fromFun f (x:xs) = (x, f x): fromFun f xs

dom [] = []
dom (x:xs) = fst x : dom xs

eval l n = snd $ head (eval' l n)

eval' l n = if l' == [] then [] else [snd $ head l']
				where l' = filter (\x -> fst x == n) l
-- eval' удобнее использовать в след. задачах

invert [] = []
invert (x@(a,b):xs) = (b,a) : invert xs

infixr 9 .*.
(.*.) _ [] = []
(.*.) [] _ = []
(.*.) t1 (x:xs) = if y' == [] then (.*.) t1 xs else (fst x, head y') : (.*.) t1 xs
				where y' = eval' t1 (snd x) 

-- [(x,t) | (x,y) <- g, (z,t) <- f, y == z]

image f s = normalize [ y | x<- s, (z,y) <- f, z == x] s

image [] _ = []
image _ [] = []
image t (y:ys) = eval' t y ++ image t ys

preimage = image . invert

isInjective t = (length $ map (fst) t) == (length $ normalize $ map (snd) t)
				where 
					normalize [] = []
					normalize (x:xs) = x : normalize [z | z<-xs, z /= x]
--
isInjective f = foldl (&&) True $ map ((==1) . length . (preimage f) . (:[]))) $ image f $ dom f

foldl (&&) True
		(map (\x -> length (preimage f [x]) == 1)(image (dom f)) )

isSurjective = (<0) . length
--любое табличное значение не сюръективно, если оно конечно, так как область значений - все целые числа

areMutuallyInverse t1 t2 = (sort t1) == (sort $ invert t2)
							where
								sort [] = []
								sort (x:xs) = sort [y | y<-xs, y <= x]  ++ [x] ++ sort [y | y<-xs, y > x]
