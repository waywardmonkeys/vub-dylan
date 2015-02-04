define class <myclass1> ( <integer> )
   slot x1 :: <integer>, init-value: 99,  init-keyword: x: ;
   slot y1 :: <integer>, init-keyword: y: ;
end class ;

define variable a :: <myclass1> = make( <myclass1>, y: 100 ) ;
define variable b :: <myclass1> = make( <myclass1>, y: 97 ) ;
a.x1 := 50 ;
print(a.x1) ;
print(a.y1) ;
print(b.x1) ;
print(b.y1) ;
