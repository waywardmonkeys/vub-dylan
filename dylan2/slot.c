#include "slot.h"
#include <string.h>
#include "expression.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : Slot_specs::Slot_specs
 | INPUT     : slot_adjective : het slot adjectief (open, sealed, ..)
 |             slot_allocation : de storage allocatie (virtual,
 |                               inherited , constant )
 |             const char * : naam van de getter
 |             DylanObject : type van het slot
 |             List<Property *> : een lijst van properties
 | OUTPUT    : -
 | RETURN    : een slot
 | DATE      :
 |
 | ABSTRACT  : Constructor van een slot binnen een class.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Slot_specs::Slot_specs( slot_adjectives AnAdjective,
                         slot_allocation AnAllocation,
                         const char *getter,
                         DylanObject *Ptr , 
                         List<Property *> *Properties) 
{
  int i ;
  char *s ;
  s = new char[255] ;

  adjective = AnAdjective ;
  allocation = AnAllocation ;
  getter_name = getter ;
  setter_name = NULL;
  strcpy(s, getter) ;
  strcat(s, ":" );
  init_keyword = s ;
  req_init_keyword = NULL;
  slot_type = Ptr;
  for( i = 1; Properties != NULL && i<= Properties->GetSize(); i++ )
  {
     Properties->MoveTo(i) ;
     if ( strcmp(Properties->GetItem()->keyword, "setter:") == 0 )
     {
       // setter_name = Properties.GetItem()->value->GetValue()->Values ;
     }
     else if ( strcmp(Properties->GetItem()->keyword, "init-value:") == 0 )
     {
        init = Properties->GetItem()->value->GetValue(NULL) ;
     }
     else if ( strcmp(Properties->GetItem()->keyword, "init-function:") == 0 )
     {
       init_function = Properties->GetItem()->value->GetValue(NULL) ;
     }
     else if ( strcmp(Properties->GetItem()->keyword, "init-keyword:") == 0 )
     {
       char *s ;
       s = new char[255] ;
       Properties->GetItem()->value->GetValue(NULL)->Getter(s) ;
       init_keyword = s ;
     }
     else if ( strcmp(Properties->GetItem()->keyword, "required-init-keyword:") == 0 )
     {
       char *s ;
       s = new char[255] ;
       Properties->GetItem()->value->GetValue(NULL)->Getter(s) ;
       req_init_keyword = s ;
     }
  }
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Slot_specs::Slot_specs
 | INPUT     :
 | OUTPUT    :
 | RETURN    :
 | DATE      :
 |
 | ABSTRACT  : Dit is de copy constructor voor slots 
 |             (wordt gebruikt binnen de copy van een klasse).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Slot_specs::Slot_specs( slot_adjectives AnAdjective,
                        slot_allocation AnAllocation,
                        const char *getter,
                        DylanObject *Ptr , 
                        DylanObject *Init, 
                        const char *keyw,
                        const char *reqkeyw )
{
  adjective = AnAdjective ;
  allocation = AnAllocation ;
  getter_name = getter ;
  setter_name = NULL;
  slot_type = Ptr;
  init = Init ;
  init_keyword = keyw ;
  req_init_keyword = reqkeyw ;
}

