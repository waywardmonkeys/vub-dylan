define variable a :: <integer> = 0 ; 
define variable b :: <double-float> = 0 ; 

define method double ( n :: <integer> )
    n * n ;
end method ;

define method double ( n :: <double-float> )
    n * n ;
end method ;

define method double ( n :: <double-float>, a :: <double-float> )
    let z = method (n :: <integer> ) n * n end method ;

    z(2) ;
end method ;

define method fac ( m :: <integer> )
   print(m) ;
   if ( m > 1 )
      m * m - 1 ;
   end if ;
end method ;

a := fac(5) ;
print( a ) ;

b ;
