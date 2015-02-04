define method g( f :: <list> )
   let length :: <integer> = size(f) ;
   let i :: <integer> = 0 ;

   while ( i < length )
      print(f[i]) ;
      i := i + 1 ;
   end while ;
end method ;

g( #(1,2,3,4,5) ) ;

g( #('a','b','c','d','e','f','g','h') ) ;

#t; 
