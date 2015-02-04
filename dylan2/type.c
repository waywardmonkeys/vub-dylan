#include "type.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : type::type
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een type object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een type object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
type::type() 
{ 
   id = "<type>"; 
   Abstract = TRUE ; 
   Sealed = TRUE; 
   Instantiable = FALSE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}

