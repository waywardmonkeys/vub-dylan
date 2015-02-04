
define method b ( h :: <function> ) 
   write( "b !!!!" ) ;
   h(2) ;
end method ;

define method c( ) 
   let y :: <integer> = 10 ;
   local method z ( x ) x + y end method ;
   write( z(5) ) ;
   b( z ) ;
end method ;
c() ;
