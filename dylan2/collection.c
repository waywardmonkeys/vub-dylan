#include "collection.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : collection::collection
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : instance van een collection
 | DATE      :
 |
 | ABSTRACT  : dient om een hierarchie te kunnen bouwen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
collection::collection() 
{ 
   id = "<collection>"; 
   Abstract = TRUE ; 
   Sealed = FALSE; 
   Instantiable = FALSE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ; 
} 

