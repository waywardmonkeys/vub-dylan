define variable a :: <integer> = 10 ;
define variable b :: <integer> = 11 ;
define variable c :: <integer> = 12 ;
define variable d :: <integer> = 13 ;
define variable e :: <integer> = 14 ;

define method boe ( x :: <integer> ,  y :: <integer> ) ;
     1257 ;
end method ;
define method test ( x :: <integer> , #rest f ) ;
     x + f[0] + f[1]  ;
end method ;
test( a , b , c ,d ,e ) ;
