define method fac( n :: <integer> ) ;
   let j :: <integer> = n ;

   while ( n > 1 )
     j := j * ( n - 1 ) ;
     n := n - 1 ;
   end while ;
   j ;
end method ;

fac(10) ; 
