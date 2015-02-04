/*
 +------------------------------------------------------------------
 | FILENAME  : character.h
 | DATE      : 26/12/1994
 |
 | ABSTRACT  : implementatie van de dylan klasse character.
 |             is identiek aan het char type van C.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/

#ifndef _CHARACTER
#define _CHARACTER
#include "object.h"
class character : public DylanObject
{
   private :
      char c ;
   public :
     character() ;
     character(char s) ;

    int operator== (const DylanObject *X) ;
     void Setter(char s) ;
     void Getter(char *s) ;
     void Print(int *) ;  
} ;
#endif
