define abstract class <abstractdict> ( <object> )
   slot size :: <integer> , init-value: 0 ;
end class ;

define class <smalldict> ( <abstractdict> )
   slot names :: <array> ;
end class ;

define class <fastdict> ( <abstractdict> )
   slot names :: <array> ;
end class ;

define method size( x :: <smalldict> )
   size(x.names) ;
end ;

define method at ( x :: <abstractdict> )
    print( "at" ) ;
    atindex ( x ) ;
end method ;

define method atindex ( x :: <smalldict> )
    print( "atindex smalldict" ) ;
end method ;

define method atindex ( x :: <fastdict> )
    print( "atindex fastdict" ) ;
end method ;

define variable mydict :: <smalldict> = 
     make( <smalldict>, names: make( <array>, dimensions: #(10) )) ;
define variable mydict1 :: <fastdict> = 
     make( <fastdict>, names: make( <array>, dimensions: #(10) )) ;
at( mydict ) ;
at( mydict1 ) ;
