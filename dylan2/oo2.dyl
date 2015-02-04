define class test ( <object> )
   slot x :: <integer>, init-value: 0 , init-keyword: x: ;
   slot y :: <integer>, init-value: 0 , init-keyword: y: ;
   slot f :: <function>, init-keyword: f: ;
end class ;
define constant b :: <function> =
    method ( x,y ) x + y ; end method ;

define variable a :: test = make( test, x: 100, y: 200, f: b ) ;

define method doiets( x :: test ) 
   x.f( x.x, x.y ) ;
end method ;

doiets(a) ;
