#ifndef _VECTOR
#define _VECTOR
#include "array.h"
class vector : public array
{
   private :
     List<DylanObject *> *Internal ;

   public :
    vector() ;
    vector(List<DylanObject *> *l )  ;

    void Getter(List<DylanObject *> *l ) ;
    void Print( int *i ) ;
    int Size() ;
    DylanObject *GetElement(int i ) ; 
    void Setter(int index, DylanObject *Obj ) ;
    Boolean Empty() ;
} ;
#endif
