define abstract class <myrange> (<sequence>)
   slot range-from :: <real>,
      init-value: 0,
      init-keyword: from:;
   slot range-by :: <real>,
      init-value: 1,
      init-keyword: by:;
   virtual slot range-direction,
      setter: #f;
end class;

define class <myrange1> (<myrange>)
   slot range-from :: <real>,
      init-value: 0,
      init-keyword: from:;
   slot range-by :: <real>,
      init-value: 1,
      init-keyword: by:;
   slot range-size :: <real>,
      init-value: 0,
      init-keyword: size:;
   virtual slot range-direction,
      setter: #f;
end class;

define method element (range :: <myrange1>, key :: <integer> )
      
   if ( (key >= 0) & (key < range.range-size) )
         range.range-from + (key * range.range-by);
   else 
      #f
   end if ;
end method;

define variable x :: <myrange1> = make( <myrange1>, from: 10, by:2, size: 1000 ) ;

element( x, 10 ) ;
