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
      const char *getter_name ;
      const char *setter_name ;
      DylanObject *slot_type ;
      const char *init_keyword ;
      const char *req_init_keyword ;
      DylanObject *init ;
      DylanObject *init_function ;
   public :
      Slot_specs( slot_adjectives AnAdjective,
                  slot_allocation AnAllocation,
                  const char *getter,
                  DylanObject *Ptr , 
                  List<Property *> *Properties ) ;
      Slot_specs( slot_adjectives AnAdjective,
                  slot_allocation AnAllocation,
                  const char *getter,
                  DylanObject *Ptr , 
                  DylanObject *Init,
                  const char *keyw,
                  const char *reqkeyw ) ;
     const char *GetGetterName() { return getter_name ; }
     const char *GetSetterName() { return setter_name ; }
     DylanObject *GetType() { return slot_type ; }
     DylanObject *GetValue() { return init ; }
     void SetValue(DylanObject *o) { init = o ; }
     const char *GetInitKeyword() { return init_keyword ; }
     const char *GetReqInitKeyword() { return req_init_keyword ; }
     DylanObject *GetInitFunction() { return init_function ; }
     slot_adjectives GetSlotAdjective() { return adjective ; }
     slot_allocation GetSlotAllocation() { return allocation ; }
     void Print(int *) { ;} 
} ;
#endif
