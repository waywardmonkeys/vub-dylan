// dit is het account voorbeeld van Abelson & Sussman
// p 173 - 178

define method make-account( balance )
   let withdraw = method( amount ) 
                     if ( balance >= amount )
                           balance := balance - amount ;
                           balance ;
                     else
                           write( "Insufficient funds"); 
                     end if ;
                  end method ;
   let deposit = method ( amount )
                    balance := balance + amount ;
                    balance ;
                 end method ;
   let dispatch = method ( m  )
                    case 
                    m = ^account- => withdraw ;;
                    m = ^account+ => deposit ;; 
                    m = ^saldo => write( balance ) ; ;
                    otherwise => write( "unknown operator !" ); ;
                    end case ;
                  end method ;
   dispatch ;
end method ;

define variable peter-acc = make-account( 100 ) ;
define variable paul-acc = make-account( 100 ) ;
define variable jan-acc = paul-acc ;
peter-acc(^account+)( 50 ) ;
paul-acc(^account-)( 30 ) ;
peter-acc(^saldo) ;
paul-acc(^saldo) ;
jan-acc(^saldo) ;
