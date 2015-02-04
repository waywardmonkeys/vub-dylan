#ifndef _VALUES_LIST
#define _VALUES_LIST
#include "list_type.h"
class values_list : public list
{
   private:
   public:
     values_list() ;

     values_list(List<DylanObject *> *l ) ; 
} ;
#endif
