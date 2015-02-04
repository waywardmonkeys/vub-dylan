
define method apply( f :: <function>, #rest args )
   let l = size(args) - 1 ;
   if ( subtype?( object-class(args[l]), <sequence> ) )
       let l2 = size(args[l]) - 1 ;
       let newargs = make( <list>, size: (l + l2 + 1 ) ) ;
       let i :: <integer> = 0 ;
       let j :: <integer> = 0 ;

       while ( i < l )
          newargs[i] := args[i] ;
          i := i + 1 ;
       end while ;

       while ( j <= l2 )
          newargs[i] := args[l][j] ;
          i := i + 1 ;
          j := j + 1 ;
       end while ;

       %apply( f, newargs ) ;
   else
      print( "Last argument must be a sequence !" ) ;
   end if ;

end method ;
define method compose (function, #rest more-functions)
  write( more-functions ) ;
  if (empty?(more-functions))
    function;
  else
    let next = apply(compose, more-functions);
    method (#rest args)
      function(apply(next, args));
    end method;
  end if;
end method;

define method complement (predicate)
  method (#rest args)
    ~apply(predicate, args);
  end method;
end method;

define method disjoin (predicate, #rest more-predicates)
  if (empty?(more-predicates))
    predicate;
  else
    let next = apply(disjoin, more-predicates);
    method (#rest args)
      apply(predicate, args) | apply(next, args);
    end method;
  end if;
end method;

define method conjoin (predicate, #rest more-predicates)
  if (empty?(more-predicates))
    predicate;
  else
    let next = apply(conjoin, more-predicates);
    method (#rest args)
      apply(predicate, args) & apply(next, args);
    end method;
  end if;
end method;

define method curry (function, #rest curried-args)
  method (#rest args)
    apply-curry(function, curried-args, args);
  end method;
end method;

define method rcurry (function, #rest curried-args)
  method (#rest args)
    apply-curry(function, args, curried-args);
  end method;
end method;

define method always (object)
  method (#rest args)
    object;
  end method;
end method;


define method generic-apply (function :: <function>, #rest arguments)
  let num-regular-args = size(arguments) - 1;
  let more-args = arguments[ num-regular-args];
  let new-args = make(<list>, size: num-regular-args + size(more-args));
  for (i from 0 below num-regular-args)
    new-args[i] := arguments[i];
  end for;
  for (arg in more-args, i from num-regular-args)
    new-args[i] := arg;
  end for;
  apply(function, new-args);
end method;

generic-apply( \+, #(10,20) ) ;

compose( \+, \*, \- ) ;
