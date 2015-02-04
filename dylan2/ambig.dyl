define method p ( x :: <real>, y :: <integer> )
   10 ;
end method ;

define method p ( x :: <integer>, y :: <integer> )
   15 ;
end method ;
define method p ( x :: <integer>, y :: <real> )
   15 ;
end method ;


define method g ( x :: <integer>, y :: <integer> )
   x + y  ;
end method ;
define method g ( x :: <float> , y :: <integer> )
   x + y  ;
end method ;

p ( 10, 10 ) ;

