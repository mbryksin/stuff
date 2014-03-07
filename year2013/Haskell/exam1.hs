zipWith' _ _ [] = []
zipWith' _ [] _ = []
zipWith' f (x1:xs1) (x2:xs2) = (f x1 x2):(zipWith' f xs1 xs2)

sprod [] [] = 0
sprod (x:xs) (y:ys) = x*y + (sprod xs ys)

normalize [] = []
normalize (l:ls) = l:(normalize(filter (/=l) ls))

sort [] = []
sort (x:xs) = sort x1 ++ [x] ++ sort x2 
     	      	   where 
		   	 x1 = [y | y<-xs, y <= x] 
			 x2 = [y | y<-xs, y > x]

isProgression [] = True
isProgression (x:[]) = True
isProgression list = flist (zipWith' (-) list (tail list)) == []
		     	   where flist dl = filter (/= (head dl)) dl 

isFunction r = length r == (length . normalize . (map fst)) r

closure r = if length r == length r' then r else closure r'
		where r' = normalize(r ++ [(x,t)| (x,y) <- r, (z,t) <- r, z == y])