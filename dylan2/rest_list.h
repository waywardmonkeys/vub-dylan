#ifndef _REST_LIST
#define _REST_LIST
#include "list_type.h"
class rest_list : public list
{
   private:
   public:
     rest_list() ;
     rest_list(List<DylanObject *> *l ) ;

     int ReturnParaType() ;

} ;
#endif
