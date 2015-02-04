define class boolean ( <class> )
   slot bool , init-keyword: bool: ;
end class ;

define constant true :: boolean = make( boolean, bool: 1) ;
define constant false :: boolean = make( boolean, bool: 0) ;

define method print( x :: boolean )
   if ( x.bool = 0 )
      print( #f ) ;
   else
      print( #t ) ;
   end if ;
end method ;

print(true) ;
