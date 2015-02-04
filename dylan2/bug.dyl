
define method member?( value , collection :: <collection> )
  let i :: <integer> = 0 ;
  let obj = #f ;
  let x = #f ;
  write( "begin member", object-class(x) ) ;
  obj := collection[1] ;
  x := #t ;
  write( "end member ", x ) ;
  x ;
end method ;

define method intersection ( s1 :: <sequence>, s2 :: <sequence> )
   let l :: <list> = #() ;
   let j :: <integer> = 0 ;
   let i :: <integer> = 0 ;
   while ( j < size(s1) )
      write( "j = ", j ) ;
      if ( member?( s1[j] , s2) ) 
         print( "a" ) ;
      end if ;
      j := j + 1 ;
   end while ;
   l ;
end method ;

intersection( #(1,9,12,14,5) , #(10,9,5,3,7) ) ;

