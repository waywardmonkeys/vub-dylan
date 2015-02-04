define class A ( <object> ) 
   slot x :: <integer>, init-value:0;
end class ;
define class B ( A )
   slot x :: <integer>, init-value:0;
end class ;
define class C ( A )
   slot x :: <integer>, init-value:0;
end class ;

define method p ( a :: A, b :: B ) print( 1 ) ; end ;
define method p ( a :: A, c :: C ) print( 4 ) ; end ;
define method p ( b :: B, a :: A ) print( 3 ) ; end ;
define method p ( a :: A, x :: A ) print( 2 ) ; end ;
define variable x1 :: A = make(A) ;
define variable x2 :: B = make(B) ;
define variable x3 :: C = make(C) ;

print(0) ;

p(x1, x2 ) ;

0 ;
