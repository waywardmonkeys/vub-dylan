define method main (#rest names)
  if (empty?(names))
    spew(*standard-input*);
  else
    for (name in names)
      let stream = if (name = "-")
		     make(<fd-stream>, fd: 0);
		   else
		     make(<file-stream>, name: name);
		   end ;
      spew(stream);
      close(stream);
    end;
  end ;
end;

define method spew (stream :: <stream>)
  if (next ~= stop)
    write(buf, *standard-output*, start: next, end: stop);
  end if;
  for (stop = fill-input-buffer(stream, 0)
	 then fill-input-buffer(stream, 0),
       until stop = 0)
    write(buf, *standard-output*, start: 0, end: stop);
  end for;
  release-input-buffer(stream, 0, 0);
end method;

main( #() ) ;
