define method test ( a1 :: <integer>, x :: <integer>, #key b: b, c: c ) ;

   print( a1 + x + b ) ;
end method ;

test( 10, 10, b: 100, c: 75 ) ;
