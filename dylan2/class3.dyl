
define class <myclass1> ( <integer> )
   slot x1 :: <integer>, init-value: 5 ;
   slot y1 :: <function>, init-function: \= ;
end class ;
print( "define var") ;

define variable c = #f ;

define variable a :: <function> = method(x) x * x end method ;

define variable b :: <function> = method(n) n + n end method ;

print( "define boe") ;

define method boe ( x :: <function>, y :: <function> ) ;
  x(9) + y(5) ;
end method ;
print("execute a") ;
c := a(10) ;
print(c) ;
c := b(7); 
print(c) ;

c := boe( a , b ) ;
print(c) ;

if ( instance? ( a, <function> ) )
   print( 1 ) ; 
else
   print (0) ;
end if ;


print ( instance?( a, <function> ) );
