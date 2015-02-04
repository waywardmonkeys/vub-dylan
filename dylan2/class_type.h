#ifndef _CLASS_TYPE
#define _CLASS_TYPE
#include "slot.h"
#include "keyword.h"

enum class_adjectives { sealed_class = 1, 
                        open_class = 2, 
                        abstract_class = 4, 
                        concrete_class = 8, 
                        primary_class = 16, 
                        free_class = 32 } ;
class class_type : public DylanObject
{
   private:
      class_adjectives   ClassAdj ;
      List<Slot_specs *> *Slots ;

   public:
      class_type() ;
      class_type(char *s, List<DylanObject *> *L1, List<Slot_specs *> *L2) ;
      class_type( DylanObject *, List<Slot_specs *> *, List<DylanObject *> *) ;
      DylanObject *Instance(DylanObject *X, List<DylanObject *> *l) ;

      void SetClassAdj( class_adjectives a) ;
      void Print(int *) ;
      Slot_specs *ReturnSlot(char *s ) ;
      List<Slot_specs *> *GetSlots()  ;
      void Initialize( List<DylanObject *> *InitList ) ;
      Boolean IsAbstract() { return (ClassAdj & 4 ) ; }
} ;
#endif
