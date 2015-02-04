define method fac-recur( x == 0)

    1 ;
end method ;

define method fac-iter( x )
   let y :: <double-float> = 1.0 ;
   for( i from 1 to x)
      y := y * i ;
   end for ;
   y ;
end method ;
define method fac-recur( x )
    x * fac-recur(x - 1) ;
end method ;
write( "fac(20) = ", fac-iter(20) ) ;
