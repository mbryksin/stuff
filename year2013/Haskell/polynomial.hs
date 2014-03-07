--16september2013 by Bryksin Matvey 
--rational numbers
reduce (a,b) = if a == 0 then (0,0) else let g = gcd a b in (div a g, div b g)
infix 6 +? -- сложение дробей
infix 6 -? -- вычитание дробей
infix 7 *? -- умножение дробей
infix 7 /? -- деление дробей

-- нормализация знака. -0 = 0 (-2,-3) = (2,3)

(--!) (x1,y1) = (-x1,y1) -- умножение на -1

(x1,y1) +? (0,0) = (x1,y1)
(0,0) +? (x1,y1) = (x1,y1)
(x1,y1) +? (x2,y2) = reduce (x1*y2 + x2*y1, y1*y2)

p1@(x1,y1) -? p2@(x2,y2) = p1 +? (--!) p2 

(x1,y1) *? (0,0) = (0,0)
(0,0) *? (x1,y1) = (0,0)
(x1,y1) *? (x2,y2) = reduce (x1*x2, y1*y2)
p1@(x1,y1) /? (x2,y2) = p1 *? (y2,x2) 
--polinomial
infix 6 +$ -- сложение полиномов
infix 6 -$ -- вычитание полиномов
infix 7 *$ -- умножение полиномов
--infix 7 /$ -- деление полиномов
--[(1,3),(2,7),(-3,4),(1,5)] == 1/3 + 2/7*x - 3/4*x^2 + 1/5*x^3 

[] +$ pat@((p,q):tl) = pat
pat@((p,q):tl) +$ [] = pat
(hd1@(p1,q1):tl1) +$ (hd2@(p2,q2):tl2) =
		  (hd1 +? hd2):(tl1 +$ tl2)

pat1@((p1,q1):tl1) -$ pat2@((p2,q2):tl2) =
		   let neg [] = []
		       neg (hd:tl) = ((--!) hd):(neg tl) 
		   in pat1 +$ (neg pat2)

(hd:tl) *$ [] = []
[] *$ (hd:tl) = []
pat1@(hd1:tl1) *$ pat2@(hd2:tl2) =
	       iterplus 0 pat1 where
		       iterplus _ [] = []
		       iterplus i pat1@(hd1:tl1) =
			   let itermult _ [] = []
			       itermult i pat2@(hd2:tl2) 
	 		          | i > 0 = (0,0):(itermult (i-1) pat2)
	 		          | True = (hd1 *? hd2):(itermult i tl2)
		       	   in itermult i pat2 +$ iterplus (i+1) tl1 

--divide dividend divisor = 
--       | length divisor < length dividend = divide dividend (0,0):divisor
--       | length divisor == length dividend = ([last dividend *? last divisor] *$ divisor)
															                                      
--pat1@(hd1:tl1) /$ pat2@(hd2:tl2) =
	       