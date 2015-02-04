define method compose (function, #rest more-functions)
  if (empty?(more-functions))
    function;
  else
    method (#rest args)
      let l = size( more-functions ) - 1 ;
      let x :: <object> = #() ;
      x := more-functions[l] ( args[0] ) ;
      l := l - 1 ;
      while ( l >= 0 )
         x :=  more-functions[l]( x );
         l := l - 1 ;
      end while ;
      function(x) ;
    end method;
  end if;
end method;

define method fac( x :: <float> )
   write( "float fac scheduled") ;
   fac( round(x) ) ;
end method ;

define method fac( x :: <integer> )
   x * fac( x - 1 ) ;
end method ;

define method fac( x == 0 )
   1 ;
end method ;

define variable perform = compose( write, fac ) ;

perform( 5.25 ) ;
