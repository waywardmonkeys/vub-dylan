define method delay( s )
   method ()
      s ;
   end method ;
end method ;

define method force ( s )
   s() ;
end method ;

define method cons-stream( a ,b )
   list( a , b ) ;
end method ;

define method head ( s )
   s[0] ;
end method ;

define method tail( s)
 force ( s[1] ) ;
end method ;
define variable n = 0 ;

define method integers-starting-from ( ) 
   n := n + 1 ;
   cons-stream ( n , method ()
                        integers-starting-from(  ) ;
                     end method ) ;
end method ;

define variable integers = integers-starting-from() ;

integers[1]()[1]() ;
