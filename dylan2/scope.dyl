define variable r :: <integer> = 0 ;

define method scope ( x :: <object> )
   let b :: <integer> = x ;
   print(b) ;
   print( r ) ;
   begin
      let r :: <double-float> = 10.0 ;
      print ( r ) ;
      r := 25.0 ;
      print( r ) ;
   end ;
   print( r ) ;
end method ;  
scope(1) ;
print( "-----------------" ) ;
scope(2) ;
