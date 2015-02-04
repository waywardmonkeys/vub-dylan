define method cell( value :: <object> )
   method ( b )
      value := value + b ;
      value ;
  end method ;
end method ;

define variable a = cell( 15 ) ;
define variable b = cell( 25 ) ;
print("koekoek") ;
print(a(1)) ;
print(b(15)) ;
print(a(1)) ;
print(a(1)) ;
print(a(1)) ;
print(a(1)) ;
print(b(15)) ;
print(b(15)) ;
print(b(15)) ;


