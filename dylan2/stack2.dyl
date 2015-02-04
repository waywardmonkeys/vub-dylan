define class <deque> ( <mutable-sequence> )
   slot max :: <integer>, init-value: 0 ;
   slot x :: <list>, init-value: #() ;
end class ;

define method push( d :: <deque>, el :: <object> )
   d.x := add( d.x, el ) ;
   d.max := d.max + 1 ;
end method ;

define method push-last( d :: <deque>, el :: <object> )
   let l :: <list> = list( el ) ;
   let i :: <integer> = 0 ;

   while( i <= (d.max - 1) ) 
        l := add( l, d.x[i] ) ;
        i := i + 1 ;
   end while ;
   d.x := l ;
   d.max := d.max + 1 ;
end method ;

define method pop( d :: <deque> )
   let el1 :: <object> = #f;
   let i :: <integer> = 0 ;
   let l :: <list> = #() ;
   
   if ( d.max <= 0 )
      write( "deque is empty" ) ;
   else
     while( i <= (d.max - 2) ) 
        l := add( l, d.x[i] ) ;
        i := i + 1 ;
     end while ;
     d.max := d.max - 1 ;
     el1 := d.x[d.max]  ;
     d.x := l ;
     el1 ;
   end if ;
end method ;

define method pop-last( d :: <deque> )
   let el1 :: <object> = #f;
   let i :: <integer> = 1 ;
   let l :: <list> = #() ;
  

   if ( d.max <= 0 )
      write( "deque is empty" ) ;
   else
     el1 := d.x[0] ;
     while( i <= (d.max - 1) ) 
        l := add( l, d.x[i] ) ;
        i := i + 1 ;
     end while ;
     d.max := d.max - 1 ;
     d.x := l ;
     el1 ;
   end if ;
end method ;

