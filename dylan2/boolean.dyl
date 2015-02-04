// implementatie van een if
// definitie van de abstracte class boolean

define abstract class boolean ( <object> )
end class ;

// klasse <true>, subclasse van boolean
define class <true> ( boolean )
   slot t, init-value: #t ;
end class ;

// klasse <false>, subclasse van boolean
define class <false> ( boolean )
   slot f, init-value: #f ;
end class ;

define method iftrue( cond :: <true>, then_block, else_block )
  then_block() ;
end method ;

define method iftrue( cond :: <false>, then_block, else_block )
  else_block() ;
end method ;

define method myif( cond , then_block, else_block )
  iftrue( cond(), then_block , else_block ) ;
end method ;

define method een_test()
   make( <false> );
end method ;

define method een()
   write( "dit is een !" ) ;
end method ;

define method twee()
   write( "dit is twee !" ) ;
end method ;

myif( een_test, een, twee );
