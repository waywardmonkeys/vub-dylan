define method remainder( a , b )
    ( a / b - floor( a /b ) ) * b ;
end method ;

define method gcd ( a , b )
   if ( b = 0 )
       a ;
   else
      gcd ( b , remainder(a,b) ) ;
   end if ;
end method ;

define method rand-update( x )
     random(x) ;
end method ;

define method rand()
     let x = 997 ;
     method()
        x := rand-update(x) ;
        x ;
     end method ;
end method ;
define variable rand = rand() ;

define constant cesaro-test = method() 
     gcd( rand(), rand()) = 1 ; end method ;

define method monte-carlo( trials, experiment :: <function> )
   let iter = method ( f , trials-remaining, trials-passed )
           write( trials-remaining, " ", trials," ", trials-passed ) ;
           case
              trials-remaining = 0 => 
                         trials-passed / trials ;; 
              experiment() =>
                         f(f , (trials-remaining - 1), (trials-passed + 1) ) ;;
              otherwise => 
                         f(f , (trials-remaining - 1), trials-passed ) ;;
           end case ;
           end method ;
  iter( iter, trials, 0 ) ;
end method ;

define method estimate-pi ( trials )
   sqrt ( 6 / monte-carlo( trials, cesaro-test ) ) ;
end method ;


estimate-pi( 100 ) ;
