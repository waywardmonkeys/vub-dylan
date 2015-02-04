define constant ne = method ( x :: <number>, y :: <number> )
   if ( x = y )
       #f ;
   else 
       #t ;
   end if ;
end method ;

define method doiets( f :: <function>, y :: <double-float> ) ;
     f(y, 100.0) ;
end method ;

doiets( ne, 100.0 ) ;
