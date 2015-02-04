#ifndef _MUTABLE_SEQUENCE
#define _MUTABLE_SEQUENCE
#include "sequence.h"

class mutable_sequence : public sequence
{
   private :
   public :
     mutable_sequence() ; 
     List<DylanObject *> *GetDimensions() ;

  protected :
     List<DylanObject *> *Dimensions ;

} ;
#endif
