define variable a :: <integer> = 0 ;
define variable i :: <integer> = 0 ;

define method unles ( condition, body )
   if ( ~condition() )
       body() ;
   else
       #f ;
   end if ;
end method ;

/*unless( i < 100 ) 
   i := i + 1 ;
   a := a + i ;
end unless ;
*/

unles( method() i < 100 ; end method ,
        method() i := i + 1 ; a := a + i ; end method ) ; 
