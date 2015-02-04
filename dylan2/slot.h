#ifndef _SLOT
#define _SLOT
#include "object.h"
#include "property.h"
enum slot_adjectives { noadj, open_slot, sealed, open_sealed, inherited } ;
enum slot_allocation { noalloc, instance, dylan_class, subclass, constant_class, virtual_class } ;

class Slot_specs
{
   private :
      slot_adjectives  adjective ;
      slot_allocation  allocation ;
      char *getter_name ;
      char *setter_name ;
      DylanObject *slot_type ;
      char *init_keyword ;
      char *req_init_keyword ;
      DylanObject *init ;
      DylanObject *init_function ;
   public :
      Slot_specs( slot_adjectives AnAdjective,
                  slot_allocation AnAllocation,
                  char *getter,
                  DylanObject *Ptr , 
                  List<Property *> *Properties ) ;
      Slot_specs( slot_adjectives AnAdjective,
                  slot_allocation AnAllocation,
                  char *getter,
                  DylanObject *Ptr , 
                  DylanObject *Init,
                  char *keyw,
                  char *reqkeyw ) ;
     char *GetGetterName() { return getter_name ; }
     char *GetSetterName() { return setter_name ; }
     DylanObject *GetType() { return slot_type ; }
     DylanObject *GetValue() { return init ; }
     void SetValue(DylanObject *o) { init = o ; }
     char *GetInitKeyword() { return init_keyword ; }
     char *GetReqInitKeyword() { return req_init_keyword ; }
     DylanObject *GetInitFunction() { return init_function ; }
     slot_adjectives GetSlotAdjective() { return adjective ; }
     slot_allocation GetSlotAllocation() { return allocation ; }
     void Print(int *) { ;} 
} ;
#endif
