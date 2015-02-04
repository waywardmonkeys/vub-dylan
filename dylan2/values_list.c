
#include "values_list.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : values-list::values-list
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : values list
 | DATE      :
 |
 | ABSTRACT  : Constructor van een values list object 
 |             dit object is in die zin bijzonder dat het in feite 
 |             een return value is van een methode
 |             (een methode die multiple values teruggeeft ).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
values_list::values_list() 
{ 
   id = "<values-list>"; 
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new list ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : values-list::values-list
 | INPUT     : List<DylanObject *> : een lijst van waarden
 | OUTPUT    : -
 | RETURN    : values list
 | DATE      :
 |
 | ABSTRACT  : Constructor van een values list object 
 |             dit object is in die zin bijzonder dat het in feite 
 |             een return value is van een methode
 |             (een methode die multiple values teruggeeft ).
 |             Met een default waarde
 | CHANGES   :
 +------------------------------------------------------------------
 */
values_list::values_list(List<DylanObject *> *l ) : list(l)
{ 
   id = "<values-list>"; 
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new list ; 
}
