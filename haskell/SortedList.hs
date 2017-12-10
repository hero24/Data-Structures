
{-
    "Success is not final, failure is not fatal: it is the courage to continue that counts."
    ~ Winston Churchill
-}

module SortedList where
    {-
        Implementaion of algebraic polymorphic sorted SortedList
    -}
    data SortedList a = Nil | SortedList {fisrt::a, rest :: SortedList a} 

    {-
        insert - Takes 'SortedList' and element as argument and
                 places the element in sorted order to the SortedList
    -}
    insert :: Ord a => SortedList a -> a -> SortedList a
    insert Nil elem = SortedList elem Nil 
    insert (SortedList first rest) elem | first > elem = SortedList elem (insert rest first)
                                        | first <= elem = SortedList first (insert rest elem)

    {-
        foldr' - Takes SortedList, function and accumulator and applies
                 function to every element of a list from left to 
                 right storing result in accumulator and then 
                 returning accumulator
    -}
    foldr' :: (a -> b -> b) -> b -> SortedList a -> b
    foldr' _ v Nil = v
    foldr' f v (SortedList first rest) = f first (foldr' f v rest)

    {-
        foldl' - Takes SortedList, function and accumulator and applies
                 function to every element of a list from right to 
                 left storing result in accumulator and then 
                 returning accumulator 
    -}
    foldl' :: (a -> b -> b) -> b -> SortedList a -> b
    foldl' _ v Nil = v
    foldl' f v (SortedList first rest) = foldl' f (f first v) rest

    {-
        create_from_list - Takes a haskell list of elements Ord
                            and creates a sorted 'SortedList' from it.
    -}
    create_from_list :: Ord a => [a] -> SortedList a
    create_from_list = foldr (\x y -> insert y x) Nil 

    {-
        pretty_print - Takes a 'SortedList' and converts it to a 
                       string representation
    -}
    pretty_print :: Show a => SortedList a -> String
    pretty_print (SortedList first rest) = "[" ++ show first ++ (pretty_inside rest) ++ "]"
    
    {-
        pretty_inside - Takes a 'SortedList' and converts it to 
                        a string without surrounding brackets
                        and comma at the beggining (used for
                        extracting the middle of the list as 
                        a string in pretty_print)

    -}
    pretty_inside :: Show a => SortedList a -> String
    pretty_inside (SortedList first Nil) = "," ++ show first
    pretty_inside (SortedList first rest) = "," ++ show first ++ (pretty_inside rest)

