// create van een cycle
// Sussman - Abelson p 204

define method head( x ) 
   x[0] ;
end method ;

define method tail( x ) ;
   x[size(x) - 1 ] ; 
end method ;

define variable x = #('a','b','c','d') ;

tail(x) := x ;
x ;

