// bepalen van de vierkantswortel, met de methode van
// Newton
define method abs ( x :: <number> ) 
    if ( x < 0 )
       x * -1 ;
    else
       x ;
    end if ;
end method ;

define method newtons-sqrt( x :: <number> )
   local method close? (guess ) 
                   print( guess ) ;
                   abs( ((guess * guess) - x) ) < 0.0001 ;
                 end method ,
         method improve ( guess )
                    ( guess + ( x / guess ) ) / 2 ;
                 end method ,
         method sqrt1 ( guess )
                  if ( close? (guess) )
                      guess ;
                  else
                       sqrt1( improve(guess) ) ;
                  end if ;
                end method ;
   sqrt1( 1 ) ;
end method ;

define method boe()
    close?( 5 ) ;
end method ;
boe() ;
print( newtons-sqrt( 2.0 ) ) ;
print( newtons-sqrt( 4.0 ) ) ;
