
/*
 +------------------------------------------------------------------
 | FILENAME  : const.h
 | DATE      :
 |
 | ABSTRACT  : klasse definitie van een constituent,
 |             constituent = expression of def. vorm of declaratie
 |
 | CHANGES   : 24/12/94 : toevoegen garbage collector
 |             08/01/95 : implementatie environments
 +------------------------------------------------------------------
*/
#ifndef _CONST
#define _CONST
#include "types.h" 
class Constituent : public gc
{
   private: 
      Boolean Local ;
   public:
      virtual void Print( int * ) = 0 ;
      virtual DylanObject *GetValue(Environment *) = 0 ;
      virtual void ReEval(Environment *) = 0 ;
      void SetLocal( Boolean ok ) { Local = ok ; }
      Boolean IsLocal() { return Local ; }
} ;
#endif
