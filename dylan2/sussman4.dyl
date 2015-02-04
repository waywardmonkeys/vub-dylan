// tree recursieve manier om fibonnaci nummers te berekenen.
// 
define method fib ( n :: <integer> )
  if ( n = 0 )
      0 ; 
  else
     if ( n = 1 )
        1
     else
        fib ( n - 1) + fib (n - 2) ;
     end if ;
  end if ;
end method ;

fib( 8 ) ;

