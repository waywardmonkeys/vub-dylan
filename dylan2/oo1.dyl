define variable x :: <list> = #() ;
define variable y :: <function> = 0 ;
define variable z :: <function> = 0 ;

define variable x1 :: <integer> = 0 ;
define variable x2 :: <integer> = 0 ;
define variable abc :: <double-float> = 0.0 ;

define variable a :: <function> =
  method ( f :: <function>, a :: <integer> )
       if ( a = 0 )
         1 ;
       else
         a * f ( f, a - 1 ) ;
       end if ;
  end method ;

define method cons( x1 :: <object>, y1 :: <object> )
   write( x1, " ", y1 ) ;
   write( list(x1,y1), object-class(list(x1,y1)) ) ;
   list( x1, y1 ) ;
end method ;

define method test( lokaal :: <integer> )
  method ( x :: <integer> )
      x + lokaal ;
   end method ; 
end method ;

print(a( a , 10)) ;


x := cons(5,'a') ;
print(x) ;
print("-----") ;
x := cons( x, x)  ; 
x ;

y := test( 5 ) ;
print(y(10)) ;
z := test( 1 ) ;
print(y(10)) ;
print(z(25)) ;
// 
// x1 := 5 ;
// x2 := x1 ;
// print(x1) ;
// print(x2) ;
// x1 := 11 ;
// print(x1) ;
// print(x2) ;
