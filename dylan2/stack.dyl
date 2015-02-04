
// een aantal nieuwe Dylan functies

define method abs ( x :: <number> )
    if ( x < 0 )
       x := x * -1 ;
    end if ;
    x ;
end method ;

define method min ( x :: <real>, #rest args )
   let l :: <integer> = size(args) ;
   let i :: <integer> = 0 ;
   while( i < l )
       if ( x > args[i] )
           x := args[i] ;
       end if ;
       i := i + 1 ;
  end while ;
  x ;
end method ;

define method max ( x :: <real>, #rest args )
   let l :: <integer> = size(args) ;
   let i :: <integer> = 0 ;

   while( i < l )
       if ( x < args[i] )
           x := args[i] ;
       end if ;
       i := i + 1 ;
  end while ;
  x ; 
end method ;

// complex getallen in Dylan
// creatie van een nieuwe klasse, erft van number

define class <complex> ( <number> )
   slot r :: <integer>, init-value: 0 ;
   slot i :: <integer>, init-value: 0 ;
end class ;

define method \+( x :: <complex>, y :: <complex> )
   let res :: <complex> = make( <complex> ) ;

   res.r := x.r + y.r ;
   res.i := x.i + y.i ;
   res ;
end method ;

define method \-( x :: <complex>, y :: <complex> )
   let res :: <complex> = make( <complex> ) ;

   res.r := x.r - y.r ;
   res.i := x.i - y.i ;
   res ;
end method ;

define method \*( x :: <complex>, y :: <complex> )
   let res :: <complex> = make( <complex> ) ;

   res.r := x.r * y.r - x.i * y.i ;
   res.i := x.r * y.i + x.i * y.r  ;
   res ;
end method ;

define method \/( x :: <complex>, y :: <complex> )
   let res :: <complex> = make( <complex> ) ;
   let den :: <double> = abs(y.r) + abs(y.i) ;
   if ( den = 0 )
      write( "Division by zero" );
   else
      let xrden = x.r * 1.0 / den ;
      let xiden = x.i * 1.0 / den ;
      let yrden = y.r * 1.0 / den ;
      let yiden = y.i * 1.0 / den ;
      let nrm = yrden * yrden + yiden * yiden ;
      res.r := (xrden * yrden + xiden * yiden ) / nrm ;
      res.i := (xiden * yrden + xrden * yiden ) / nrm ;
   end if ;
   res ;
end method ;

define method \=( x :: <complex>, y :: <complex> )
   x.r = y.r & x.i = y.i ;
end method ;

define method \~=( x :: <complex>, y :: <complex> )
   ~(x = y) ;
end method ;

define method print ( x :: <complex> )
   write( x.r, " + ", x.i, "i" ) ;
end method ;

define method last( l :: <collection> )
   l[size(l) - 1] ;
end method ;

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
       write( f , " - ", newargs ) ;
       %apply( f, newargs ) ;
   else
      print( "Last argument must be a sequence !" ) ;
   end if ;

end method ;

define method do ( f :: <function>, l :: <collection> ) 
   let i :: <integer> = 0 ;
   while( i < size(l) )
      f( l[i] ) ;
      i := i + 1 ;
   end while ;
end method ;

define method reduce( f :: <function>, i :: <object>, l :: <collection> )
    let z :: <object> = 0 ;
    let j :: <integer> = 1 ;
    z := f( l[0], i ) ;
    while( j < size(l) )
       z := f( l[j], z ) ;
       j := j + 1 ;
    end while ;
    z ;
end method ;

define method reduce1( f :: <function>, l :: <collection> )
    let z :: <object> = 0 ;
    let j :: <integer> = 2 ;
    z := f( l[0], l[1] ) ;
    while( j < size(l) )
       z := f( l[j], z ) ;
       j := j + 1 ;
    end while ;
    print(z) ;
    z ;
end method ;

define method map( f , l1 :: <collection>)
    let length = size(l1) ;

    let z :: <list> = make( <list>, size: length) ;
    let j :: <integer> = 0 ;
    while( j < size(l1) )
       z[j] := f( l1[j] ) ;
       j := j + 1 ;
    end while ;
    z ;
end method ;

define method find-key( l :: <collection>, f :: <function> ) 
   let i :: <integer> = 0 ;
   let found :: <integer> = 0 ;

   while ( i < size(l) )

      if ( f(l[i]) & found = 0)
         found := i ;
      end if ;
      i := i + 1 ;
   end while ;
   found ;
end method ;

define method replace-elements!( l :: <collection>, f :: <function>, g :: <function> ) ;
   let i :: <integer> = 0 ;
   while ( i < size(l) )

      if ( f(l[i]) )
         l[i] := g(l[i]) ;
      end if ;
      i := i + 1 ;
   end while ;
   l ; 
end method ;

define method add( l :: <collection>, a :: <object> )
   let l2 = make( object-class(l), size: size(l) + 1) ;
   let i = 0 ;

   while ( i < size(l) )
      l2[i] := l[i] ;
      i := i + 1 ;
   end while ;
   l2[i] := a ;
   l2 ;
end method ;

define method add!( l :: <collection>, a :: <object> )
   let l2 = make( object-class(l), size: size(l) + 1) ;
   let i = 0 ;

   while ( i < size(l) )
      l2[i] := l[i] ;
      i := i + 1 ;
   end while ;
   l2[i] := a ;
   l2 ;
end method ;

define method add-new( l :: <collection>, a :: <object> )
   let i = 0 ;
   let may-add = #t ;

   while ( i < size(l) & may-add )
      if ( l[i] = a )
         may-add := #f ;
      end if ;
      l2[i] := l[i] ;
      i := i + 1 ;
   end while ;
   if ( may-add )
      let l2 = make( object-class(l), size: size(l) + 1) ;
      i := 0 ;
      while ( i < size(l) )
         if ( l[i] = a )
            may-add := #f ;
         end if ;
         l2[i] := l[i] ;
         i := i + 1 ;
      end while ;
      l2[i] := a ;
      l2 ;
  else
      l ;
  end if ;
end method ;

define method remove( l :: <sequence>, v :: <object> ) 
   let i = 0 ;
   let l2 = make( object-class(l), size: 0) ;
   while ( i < size(l) )
      if ( l[i] = v )
         #t ;
      else
         l2 := add(l2, l[i] ) ;
      end if ;
      i := i + 1 ;
   end while ;
   l2 ;
end method ;

define method choose( f :: <function> , l :: <sequence> ) 
   let i = 0 ;
   let l2 = make( object-class(l), size: 0) ;
   while ( i < size(l) )
      if ( f(l[i] ) )
         l2 := add(l2, l[i] ) ;
      end if ;
      i := i + 1 ;
   end while ;
   l2 ;
end method ;

define method reverse( l :: <sequence> ) 
   let b :: <object> = #f ;
   let i = size(l) - 1 ;
   let j :: <integer> = 0 ;

   let l2 = make( object-class(l), size: size(l) ) ;

   while ( i >= 0 )

      l2[j] := l[i] ;
      i := i - 1 ;
      j := j + 1 ;
   end while ;
   l2 ;
end method ;

define method first( l :: <sequence> )
   l[0] ;
end method ;

define method second( l :: <sequence> )
   l[1] ;
end method ;
define method third( l :: <sequence> )
   l[2] ;
end method ;

define method as-uppercase( str :: <string> )
    let i = size(str) ;
    let x :: <string> = make( <string>, size: size(str) ) ;
    let j = 0 ;
    while( j < i )  
       x[j] := as-uppercase(str[j]);
       j := j + 1 ;
    end while ;
    x ;
end method ;

define method as-lowercase( str :: <string> )
    let i = size(str) ;
    let x :: <string> = make( <string>, size: i ) ;
    let j = 0 ;
    while( j < i )  

       x[j] := as-lowercase(str[j]);
       j := j + 1 ;
    end while ;
    x ;
end method ;

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

define method complement (function :: <function>)
    method (#rest args)
      ~apply( function, args ) ;
    end method;
end method;

define method tail(x) 
   let l2 = make( <list>, size: size(x) - 1) ; 
   let i = 1 ;
   while ( i < size(x) )
      l2[ i - 1 ] := x[i] ;
      i := i + 1 ;
   end while ;
   l2 ;
end method ;

define method \= ( l1 :: <list>, l2 :: <list> )
   if ( size(l1) = 0 )
       size(l2) = 0 ;
   else
      size(l2) = size(l1) & head(l1) = head(l2) & tail(l1) = tail(l2) ;
   end if ;
end method ;

define class <empty-list> ( <list> )
   constant slot x :: <list>, init-value: #() ;
end class ;

define constant empty-list = make( <empty-list> ) ;

define method any?( f , l :: <collection>, #rest more-collections )
   let x = size(more-collections) ;
   let y = size(l) ;
   let l2 = make( <list>, size: x + 1 ) ;
   let true_or_false = #f ;
   for ( i from 0 to y - 1 )
     l2[0] := l[i] ;
     j := 0 ;
     while ( j <=  (x - 1) )
        l2[(j + 1)] := more-collections[j][i] ;
        j := j + 1 ;
     end while ;
     if ( apply( f , l2 ) )
        true_or_false := #t ;
     end if ;
  end for ;
  true_or_false ;
end method ;

define method member?( value , collection :: <collection> )
  let i :: <integer> = 0 ;
  let x = #f ;
  while ( i < size(collection) ) 
     if ( value = collection[i] )
        x := #t ;
     end if ;
     i := i + 1 ;
  end while ;
  x ;
end method ;

define method fill! ( collection :: <mutable-collection>, value, #rest args  )
  let lower = 0 ;
  let upper = size(collection) - 1 ;

  if ( size( args ) = 1 )
      lower := args[0] ;
  end if ;
  if ( size( args ) = 2 )
      lower := args[0] ;
      upper := args[1] ;
  end if ;

  for( j from lower to upper )
     collection[j] := value ;
  end for ;
  collection ;
end method ;

define method intersection ( s1 :: <sequence>, s2 :: <sequence> )
   let l :: <list> = #() ;
   let j :: <integer> = 0 ;
   let i :: <integer> = 0 ;
   while ( j < size(s1) )
      if ( member?( s1[j] , s2) )
         l := add( l , s1[j] ) ;
      end if ;
      j := j + 1 ;
   end while ;
   l ;
end method ;

define class <array-stack> ( <object> )
   slot max :: <integer>, init-value: 0 ;
   slot x :: <list> , init-value: #() ;
end class ;

define method push( AStack :: <array-stack>, el :: <object> )
   AStack.max := AStack.max + 1 ;
   AStack.x := add( AStack.x, el) ;
end method ;

define method pop( AStack :: <array-stack> )
   let el :: <object> = #() ;

   if ( AStack.max = 0 )
      print( "Stack empty" ) ;
   else
      AStack.x[AStack.max - 1] := #f ;
      AStack.max := AStack.max - 1 ;
   end if ;
   el := AStack.x[AStack.max - 1] ;
   el ;
end method ;
define variable a :: <array-stack> =  make( <array-stack> ) ;

print( "start") ;
push( a , 11 ) ;
push( a , 11 ) ;
push( a , 12 ) ;
push( a , 13 ) ;
push( a , 14 ) ;
print(a.max) ;
write( pop( a ) ) ;
write( pop( a ) ) ;
write( pop( a ) ) ;
write( pop( a ) ) ;
print(a.max) ;
