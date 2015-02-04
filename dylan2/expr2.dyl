
define class <my-number> ( <integer> )
   slot x :: <integer>, init-value: 0 ;
end class ;
define variable x1 :: <my-number> = make(<my-number> ) ;
define variable x2 :: <my-number> = make(<my-number> ) ;

define method \+ ( x :: <my-number>, y :: <my-number> )
    x.x * y.x ;
end method ;

print( as-uppercase( 'a' ) ) ;
print( as-uppercase( 'z' ) ) ;
print( as-uppercase( 'z' ) ) ;
print( as-lowercase( 'B' ) ) ;
print( as-lowercase( 'Z' ) ) ;
