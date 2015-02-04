#ifndef _EXTENDED_FLOAT
#define _EXTENDED_FLOAT 
#include "float.h"
class extended_float : public myfloat
{
   private :
      double i ;
   public :
     extended_float() ;
     extended_float(float x) ; 
     void Setter(double s) ;
     void Getter(double *s) ;
     void Print(int *) ;  
    int operator== (const DylanObject *X) ;
} ;
#endif
