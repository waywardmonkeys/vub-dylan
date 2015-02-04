define method key-test( x :: <integer>, #key mykey: akey, xkey: bkey )
   write( "x = " , x ) ;
   write( "akey = " , akey ) ;
end method ;

key-test( 5, mykey: 10, xkey: 5 ) ;
