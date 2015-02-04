define variable a :: <integer> = 2 ;
define variable b :: <integer> = 2 ;
define variable z :: <integer> = 0 ;

define method g( x :: <integer> ) 
   x + 5 ;
end method ;
define method f( x :: <integer> ) 
    if ( x > 1 )
       z := g(x) * 10 ;
       print(z) ;
    end if ;
    z ; 
end method ;

if ( a > 1 )
  a := f(a) + g(b);
end if ;
a ;
