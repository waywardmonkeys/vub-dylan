define method f ( x :: <integer> )
   values ( x + 1, x - 1, 1 ) ;
end method ;

define method g ( )
   let ( a ,b ) = f (10) ;
   a + b ;
end method ;

define variable ( a , b,c ,d ) = f( 5 ) ;
print( a ) ;
print( d ) ;
g( ) ;
