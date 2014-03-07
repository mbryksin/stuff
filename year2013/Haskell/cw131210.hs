{-

data E = C Int | A E E | S E E | D E E

fromInt = Just

matchMaybe :: Maybe Int -> (Int -> Maybe Int) -> Maybe Int

matchMaybe Nothing  _ = Nothing
matchMaybe (Just x) f = f x

eval (C x) = Just x
eval (A x y) = matchMaybe (eval x) (\ x -> matchMaybe (eval y) $ fromInt . (x+) )
eval (S x y) = matchMaybe (eval x) (\ x -> matchMaybe (eval y) $ fromInt . (x+) )
eval (A x y) = matchMaybe (eval x) (\ x -> matchMaybe (eval y) 
															(\ y -> if y == 0
																		then Nothing
																		else fromInt $ x `div` y)

-}
{-
class Monad m where
	return :: a -> m a   -- fromInt
	(>>=)  :: m a -> (a -> m b) -> m b --matchMaybe (bind)
	(>>)   :: m a -> m b -> m b
-}
{-
data E = X String | C Int | A E E | S E E | D E E

data Value a = Error String | Value a

instance Monad Value where
 	return a = Value a
 	(>>=) a f  = case a of
 					Error s -> Error s
 					Value a -> f a

eval s (C x) = return x
eval s (A x y) = eval s x >>= (\ x -> eval s y >>= return . (x+) )
eval s (S x y) = eval s x >>= (\ x -> eval s y >>= return . (x-) )
eval s (A x y) = eval s x >>= (\ x -> eval s y >>= (\ y -> if y == 0
														then Error "division by 0"
														else return $ x `div` y ))
eval s (X n) = s n
-}
--синтактический сахар e >>= (\x -> b) => 
--do
--  x<-e
--  f

data E = X String | C Int | A E E | S E E | D E E

data Value a = Error String | Value a

instance Monad Value where
 	return a = Value a
 	(>>=) a f  = case a of
 					Error s -> Error s
 					Value a -> f a

eval s (C x  ) = return x
eval s (A x y) = do e1 <- eval s x
					e2 <- eval s y
					return (e1 + e2)
eval s (S x y) = do	e1 <- eval s x
					e2 <- eval s y
					return (e1 - e2)
eval s (D x y) = do e1 <- eval s x
					e2 <- eval s y
					if e2 == 0
						then Error "division by 0"
						else return (e1 `div` e2)
eval s (X n) = s n


