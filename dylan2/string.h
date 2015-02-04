#ifndef _STRING
#define _STRING
#include "mutable_sequence.h"

class string : public mutable_sequence
{
   private :
      char *s ;
   public :
     string() ; 
     string(char *str) ; 
     string(int *, List<DylanObject *> *) ; 
     void Setter(char *str) ;
     void Getter(char *str) ;
     DylanObject *GetElement( int i) ;
     void Print(int *) ;  
     int operator== (const DylanObject *X) ;
     int Size() { return strlen(s) ; }
     DylanObject *Instance(DylanObject *X, List<DylanObject *> *l) ;
     void Setter(int index, DylanObject *Obj ) ;
} ;
#endif
