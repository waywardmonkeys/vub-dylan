/*
 +------------------------------------------------------------------
 | FILENAME  : boolean.h
 | DATE      : 26/12/1994
 |
 | ABSTRACT  : het boolean type (dit is normaal geen default
 |             klasse van dylan ).
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/

#ifndef _BOOLEAN
#define _BOOLEAN
#include "type.h"
class boolean_type : public type
{
   private :
      Boolean i ;
   public :
     boolean_type() ; 
     boolean_type(int x) ; 
     void Setter(int s) ;
     void Getter(int *s) ;
     void Print(int *) ;  

    int operator== (const DylanObject *X) ;
} ;
#endif
