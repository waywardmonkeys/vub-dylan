#ifndef _RANGE
#define _RANGE
#include "sequence.h"
#include "double_float.h"
class range : public sequence
{
   private :
     double from ;
     double to ;
     double above ;
     double below ;
     int size ;
     double by ;
     double_float *result ;
     double local ;

   public :
    range() ; 
    range(int *, List<DylanObject *> *l )  ;
    DylanObject *Instance(DylanObject *X, List<DylanObject *> *l) ;
              
    DylanObject *GetElement( int i ) ;
    void Setter( double x )  ;
    int operator== (const DylanObject *X) ;
} ;
#endif
