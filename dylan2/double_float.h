#ifndef _DOUBLE_FLOAT
#define _DOUBLE_FLOAT
#include "float.h"
class double_float : public myfloat
{
   private :
      double i ;
   public :
     double_float() ;
     double_float(float x) ;
     void Setter(double s) ;
     void Getter(double *s) ;
     void Print(int *) ;  
    int operator== (const DylanObject *X) ;
} ;
#endif
