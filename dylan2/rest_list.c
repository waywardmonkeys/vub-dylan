#include "rest_list.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : rest_list::rest_list
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : rest list
 | DATE      :
 |
 | ABSTRACT  : constructor van een rest list
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
rest_list::rest_list() 
{ 
   id = "<rest>"; 
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new list ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : rest::rest_list
 | INPUT     : List<DylanObject *> : een lijst
 | OUTPUT    : -
 | RETURN    : een lijst
 | DATE      :
 |
 | ABSTRACT  : Constructor van een lijst met default waarde
 |             (wordt doorgegeven aan list)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
rest_list::rest_list(List<DylanObject *> *l ) : list(l)
{ 
   id = "<rest>"; 
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new list ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : rest_list::ReturnParaType
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : type van de lijst
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int rest_list::ReturnParaType() 
{ 
   return rest_par ; 
}

