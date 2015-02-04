#ifndef _SYMBOL
#define _SYMBOL
#include "object.h"

class symbol : public DylanObject
{
   private :
      char *s ;
   public :
     /* constructors */
     symbol() ;
     symbol(char *str) ; 

     void Setter(char *str) ;
     void Getter(char *str) ;
     void Print(int *) ;
} ;
#endif
