
define class <myclass1> ( <integer> )
   slot x1 :: <integer>, init-value: 5 ;
   slot y1 :: <integer>, init-value: 0 ;
end class ;

define class <myclass> ( <integer> )
   slot x :: <myclass1>, init-value: make(<myclass1>) ;
   slot y :: <integer>, init-value: 0 ;
end class ;

define variable a :: <myclass> = make(<myclass> ) ;
define variable b :: <myclass> = make(<myclass> ) ;
define variable c :: <integer> = make(<integer>) ;
print(c) ;
a.x.x1 := 10 ;
a.x.y1 := 15 ;
b.x := 100 ;
b.y := 70 ;

print(a.x.x1) ;
print(a.x.y1) ;
print(b.x) ;
print(b.y) ;
a
