#ifndef _SINGLE_FLOAT
#define _SINGLE_FLOAT
#include "float.h"
class single_float : public myfloat
{
   private :
      float i ;
   public :
     single_float() ;
     single_float(float x) ; 
     void Setter(float s) ;
     void Getter(float *s) ;
     void Print(int *) ;  
    int operator== (const DylanObject *X) ;
} ;
#endif
