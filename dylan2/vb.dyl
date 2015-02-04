define abstract class <point> ( <object> )
   slot abs :: <boolean> , init-value: #t ;
end class ;

define class <3dpoint> ( <point> )
   slot x :: <float>, init-value: 0.0 ;
   slot y :: <float>, init-value: 0.0 ; 
   slot z :: <float>, init-value: 0.0 ;
end class ;

define class <2dpoint> ( <3dpoint> )
   inherited slot x ;
   inherited slot y ;
   constant slot z :: <float>, init-value: 0.0 ;
end class ;

define abstract class <polygoon> ( <object> )  
   constant slot naam , init-value: "polygoon" ;
end class ;

define class <square> ( <polygoon> )
   slot p1 :: <2dpoint> , init-value: make( <2dpoint> );
   slot side :: <float> , init-value: 0.0 ;
   inherited slot naam, init-value: "vierkant" ;
end class ;

define class <circle> ( <polygoon> )
   slot center :: <2dpoint> ;
   slot radius :: <float>, init-value: 0.0 ;
   inherited slot naam, init-value: "circle" ;
end class ;

define class <ellips> ( <circle> )
   inherited slot center ;
   inherited slot radius ;
   slot radius2 :: <float> ;
end class ;

define class <rectangle> ( <square> )
   slot p1 :: <2dpoint> , init-value: make( <2dpoint> );
   slot p2 :: <2dpoint> , init-value: make( <2dpoint> );
   slot p3 :: <2dpoint> , init-value: make( <2dpoint> );
   slot p4 :: <2dpoint> , init-value: make( <2dpoint> );
   inherited slot naam, init-value: "vierkant" ;
end class ;

define method init ( x == <square>, #key x1: x1 ,y1: y1,x2: x2,y2: y2,x3: x3,y3: y3,x4: x4,y4: y4)
   let p1 = make( <2dpoint>, x: x1, y: y1 ) ;
   let p2 = make( <2dpoint>, x: x2, y: y2 ) ;
   let p3 = make( <2dpoint>, x: x3, y: y3 ) ;
   let p4 = make( <2dpoint>, x: x4, y: y4 ) ;
   make( <square>, p1: p1, p2: p2, p3: p3, p4: p4 ) ;
end method ;

define method init ( x == <circle>, #key x1: x1 ,y1: y1, radius: radius ) ;
   let p1 = make( <2dpoint>, x: x1, y: y1 ) ;
   make( <circle>, center: p1, radius: radius ) ;
end method ;

define method init ( x == <ellips>, #key x1: x1 ,y1: y1, radius1: radius1, radius2: radius2 ) ;
   let p1 = make( <2dpoint>, x: x1, y: y1 ) ;
   make( <ellips>, center: p1, radius: radius1, radius2: radius2 ) ;
end method ;

define variable een_vierkant :: <square> = init ( <square>, x1: 1,y1: 2,x2: 3,y2: 4,x3: 5,y3: 6,x4: 7,y4: 8 ) ;
define variable een_cirkel :: <circle> = init ( <circle>, x1: 1,y1: 2,radius: 10.0 ) ;
define variable een_ellips :: <ellips> = init ( <ellips>, x1: 1,y1: 2,radius1: 3.0, radius2: 4.0 ) ;

een_ellips ;
