define variable y :: <range> = make( <range>, by: 5.0, from: 10.0 ) ;
define variable z :: <array> = make( <array>, dimensions: #(5,5) ) ;
print( y[2] )  ;
z[0,0] := 10 ;
print(z[0,0] ) ;
