define constant write :: <function> = method(x) print(x) end method ;

define constant max :: <function> = 
     method(x,y) if ( x > y ) x else y ; end if ; end method ;

define constant min :: <function> = 
     method(x,y) if ( x < y ) x else y ; end if ; end method ;

define constant plus :: <function> = 
     method(x,y) x + y ; end method ;

define constant double :: <function> =
     method(x) x * 2 ; end method ;

define constant even :: <function> =
     method(x) even?(x) ; end method ;

define constant eq :: <function> =
    method( x, y ) x = y ; end method ;

define method \even? ( x :: <object> )
    even(x) ; 
end method ;

define method head( l :: <collection> )
   l[0] ;
end method ;

define method tail( l :: <collection> )
   l[size(l) - 1] ;
end method ;

define method apply( f :: <function>, #rest args  )
   let l :: <object> = 0 ;
   let i :: <integer> = 0 ;

   while ( i < size(args) )
      l := args[i] ;
      f(l) ;
      i := i + 1 ;
   end while ;
   #f ;
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
    z ;
end method ;

define method map( f :: <function>, l1 :: <collection>, l2 :: <collection)
    let length = size(l1) ;

    let z :: <list> = make( <list>, size: length) ;
    let j :: <integer> = 0 ;
    while( j < size(l1) )
       z[j] := f( l1[j], l2[j] ) ;
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
   print(f) ;
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
   print(l2) ;
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
define variable x :: <list> = #(1,2,3,4,5,6,7,8,9,10,11,12) ;
define variable y :: <list> = #(10,10,10,11,50) ;
define variable z :: <list> = #() ;
define variable lijst :: <list> = #( "pistache", "ginger", "vanille" ) ;
print(reverse(x)) ;
print(first(x)) ;
print(second(x)) ;
print(third(x)) ;
print( list (5,6,7,8) ) ;
choose( even, x ) ;
#t ;
