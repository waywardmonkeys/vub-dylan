// streams
// p 245 - 292 van Sussman & Abelson
define method cons-stream( x , y )
   if ( size(y) = 0 )
       list( x ) ;
   else
       let length = size(y) + 1 ;
       let l2 = make( <list>, size: length) ;
       let i = 1 ;
       l2[0] := x ;
       while( i < size(l2) )
          l2[i] := y[i - 1] ;
          i := i + 1 ;
       end while ;
       l2 ;
   end if ;
end method ;

define method head ( x )  
   x[0] ;
end method ;

define method tail(x) 
   let l2 = make( <list>, size: size(x) - 1) ; 
   let i = 1 ;
   while ( i < size(x) )
      l2[ i - 1 ] := x[i] ;
      i := i + 1 ;
   end while ;
   l2 ;
end method ;

define method empty-stream? ( s )
   size(s) = 0 ;
end method ;

define constant the-empty-stream = #() ;

// to filter a stream for oddness
define method filter-odd( s )
   if ( empty-stream?( s) )
       the-empty-stream ;
   else
       if ( odd?( head(s) ) )
           cons-stream( head(s), filter-odd( tail(s))) ;
       else
           filter-odd( tail(s)) ;
       end if ;
   end if ;
end method ;

// accumulate (p 248)
define method accumulate( combiner, initial-value, stream )
   if ( empty-stream?( stream ))
       initial-value ;
   else
       combiner( head(stream), 
                 accumulate( combiner, initial-value, tail(stream)));
   end if ;
end method ;

// 2 voorbeelden , een sum-stream en een product-stream
define method sum-stream( s )
    accumulate( \+, 0, s ) ;
end method ;

define method product-stream(s)
   accumulate( \*, 1, s ) ;
end method ;

print( sum-stream ( #(1,2,3,4,5) ) ) ;
print( product-stream( #(1,2,3,4,5))) ;

// maps and filters

define method map ( proc, stream )
   if ( empty-stream? ( stream ) )
       the-empty-stream ;
   else
      cons-stream( proc( head(stream)),
                   map( proc, tail(stream))) ;
  end if ;
end method ;

define method filter( pred, stream )
    if ( empty-stream?( stream ) )
       the-empty-stream ;
    else
       if ( pred( head(stream ) ))
          cons-stream( head(stream),
                       filter( pred, tail(stream))) ;
       else
          filter( pred, tail(stream)) ;
       end if ;
   end if ;
end method ;

// vb van filters en maps
define constant is-odd = method (x) odd? (x) ; end method ;
define constant square = method(x) x * x ; end method ;

define method product-of-squares-of-odd-elements( stream )
   accumulate ( \*, 1 , map ( square, filter( is-odd, stream))) ;
end method ;

print( product-of-squares-of-odd-elements( #(1,2,3,4,5,6,7,8,9,10))) ;

// for-each

define method for-each( proc, stream )
   if ( empty-stream?(stream))
      write( "done" ) ;
   else
      proc( head(stream)) ;
      for-each( proc, tail(stream)) ;
   end if ;
end method ;

// vb van for-each
define constant dump = method(x) write(x) end method ;

for-each( dump, #(1,2,3,4,5,6) ) ;
