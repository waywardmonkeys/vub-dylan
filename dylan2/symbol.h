#ifndef _SYMBOL
#define _SYMBOL
#include "object.h"

class symbol : public DylanObject
{
   private :
      const char *s ;
   public :
     /* constructors */
     symbol() ;
     symbol(const char *str) ; 

     void Setter(const char *str) ;
     void Getter(char *str) ;
     void Print(int *) ;
} ;
#endif
