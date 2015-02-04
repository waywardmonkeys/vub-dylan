define variable r :: <integer> = 0 ;

define method show ( )
   print( r ) ;
end method ;  

define method nog()
     let r :: <integer> = 2 ;
     show() ;
end method ;

show() ;
nog() ;
show() ;
nog() ;
