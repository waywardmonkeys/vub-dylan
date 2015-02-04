#ifndef _INTEGER
#define _INTEGER
#include "real.h"
class integer : public real
{
   private :
      long i ;
   public :
     /* constructors */
     integer() ;
     integer(long x) ; 

     void         Setter(long s) ;
     void         Getter(long *s) ;
     void         Print(int *) ;  
     DylanObject *Instance( DylanObject *, List<DylanObject *> * ) ;
     int          operator==( const DylanObject *X) ;
} ;
#endif
