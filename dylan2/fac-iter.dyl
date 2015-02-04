
define method fac( x :: <integer> )
  let res :: <integer> = 1 ;
  let i :: <integer> = 1 ;
  while( i <= x )
     res := res * i ;
     i := i + 1 ;
  end while ;
  res ;
end method ;  

write(fac(1000)) ;
