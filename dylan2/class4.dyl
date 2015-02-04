define class <animal> ( <object>, <integer> )
   slot n-legs, init-value: 4;
   class slot boe, init-value: 1000 ;
   slot animal-a, init-keyword: an-animal: ;
end class ;

define class <spider> ( <animal> )
  slot z, init-value: 10, init-keyword: x ;
  constant slot a, init-value: 5 ;
  inherited slot n-legs, init-value: 12 ;
end class ;

define method n-legs( x :: <spider> )
   x.n-legs ;
end method ;

define variable x :: <spider> = make(<spider> ) ;
define variable y :: <animal> = make(<animal>, an-animal: 15 ) ;
print ( x.n-legs ) ;
