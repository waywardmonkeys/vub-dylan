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
define constant p = method ( x , y ) p(x,y) ; end method ;

p( make(A), make(A) ) ;
p(make(A), make(B) ) ;
p(make(B), make(A));
p ( make(B), make(B) ) ;
p(make(A), make(C) ) ;
p(make(C), make(A)) ;
p(make(C), make(C)) ;
p( make(B), make(C) ) ;
p( make(C), make(B) ) ;
#t ;

