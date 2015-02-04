define method test ( x :: <integer>, #key x: xkey , y: ykey) ;
     print(xkey) ;
     print(ykey) ;
end method ;

test( 10, x: 5, y: 10 ) ;
