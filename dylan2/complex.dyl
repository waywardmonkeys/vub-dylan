define class <complex> ( <number> )
   slot r :: <integer>, init-value: 0 ;
   slot i :: <integer>, init-value: 0 ;
end class ;

define method plus( x :: <complex>, y :: <complex> )
   let res :: <complex> = make( <complex> ) ;

   res.r := x.r + y.r ;
   res.i := x.i + y.i ;
   res ;
end method ;

define method min( x :: <complex>, y :: <complex> )
   let res :: <complex> = make( <complex> ) ;

   res.r := x.r - y.r ;
   res.i := x.i - y.i ;
   res ;
end method ;

define method print ( x :: <complex> )
   print( x.r ) ;
   print( x.i ) ;
   print(i) ;
end method ;

define variable a :: <complex> = make( <complex>, r: 1, i:5 ) ;
define variable b :: <complex> = make( <complex>, r: 5, i:1 ) ;
define variable c :: <complex> = make( <complex> ) ;
define variable d :: <complex> = make( <complex> ) ;
c := plus(a ,b )  ;
d := min( a, b )  ;
print(c) ;
print(d) ;
