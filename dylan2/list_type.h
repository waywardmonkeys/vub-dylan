#ifndef _LISTTYPE
#define _LISTTYPE
#include "mutable_sequence.h"
class list : public mutable_sequence
{
   private :
     List<DylanObject *> *Internal ;

   public :
    list() ;
    list(List<DylanObject *> *l ) ;
    list(int *, List<DylanObject *> *l )  ;

    DylanObject *Instance(DylanObject *X, List<DylanObject *> *l) ;
    DylanObject *GetElement(int i ) ; 
    void Getter(List<DylanObject *> *l ) ; 
    void Setter(int index, DylanObject *Obj ) ;
    void Print( int *i ) ;
    int Size() ;  
    Boolean Empty() ; 
} ;
#endif
