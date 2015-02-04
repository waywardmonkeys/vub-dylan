define method apply( f :: <function>, #rest args )
   let l = size(args) - 1 ;
   if ( subtype?( object-class(args[l]), <sequence> ) )
       let l2 = size(args[l]) - 1 ;
       let newargs = make( <list>, size: (l + l2 + 1 ) ) ;
       let i :: <integer> = 0 ;
       let j :: <integer> = 0 ;
       while ( i < l )
          newargs[i] := args[i] ;
          i := i + 1 ;
       end while ;

       while ( j <= l2 )
          newargs[i] := args[l][j] ;
          i := i + 1 ;
          j := j + 1 ;
       end while ;

       %apply( f, newargs ) ;
   else
      print( "Last argument must be a sequence !" ) ;
   end if ;

end method ;

define method f ( x :: <integer> )  
   x ;  
end method ;

define constant f1 :: <function> = method (#rest x ) size(x); end method ;

apply( \+,  #(20,30) );

