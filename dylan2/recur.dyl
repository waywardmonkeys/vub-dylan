define method recur( i :: <integer> )
   if ( i > 1 )
      recur(i - 1) ;
   else
      1 ;
   end if ;
   print(i) ;
   
end method ;

recur(5) ;
