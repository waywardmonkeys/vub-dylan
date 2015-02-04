/*
 +------------------------------------------------------------------
 | FILENAME  : array.h
 | DATE      : 26/12/1994
 |
 | ABSTRACT  : Implementatie van het array object van dylan.
 |             Intern wordt dit geimplementeerd als een array van
 |             pointers naar dylan objects.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/

#ifndef _ARRAY
#define _ARRAY
#include "mutable_sequence.h"

class array : public mutable_sequence
{
   private :
     DylanObject **Internal ;

   public :
    array() ;
    array(int *, List<DylanObject *> *l )  ;
    DylanObject *Instance(DylanObject *X, List<DylanObject *> *l) ;
    DylanObject *GetElement(int i ) ;
    void Setter(int index, DylanObject *Obj ) ;
    Boolean Empty() ; 
    void Print( int *i ) ;
    int operator== (const DylanObject *X) ;
    int Size() ;
} ;
#endif
