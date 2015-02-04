define method make( x :: <symbol>, dim, #key y: dim12 ) ;
   print( "boeeeeeeeee" ) ;
   write(x) ;
end method ;

define method test ( x :: <integer>, #key x: xkey , y: ykey) ;
     print(xkey) ;
     print(ykey) ;
end method ;

make( <vector>, 10, y: 10 ) ;
test( 10, x: 5, y: 10 ) ;
