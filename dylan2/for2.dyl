define method f ()
  for( i from 0 to 100 )
      write( "i = ", i ) ;
  end for ;
end method ;

define method g ()
   for ( j from 0 to 100 )
      write( " j = ", j   ) ;
      f() ;
   end for ;
end method ;
g() ;
