#include "number.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : number::number
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een number object
 | DATE      :
 |
 | ABSTRACT  : Constructor voor een number object
 |             superklasse van alle soorten getallen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
number::number() 
{ 
   id = "<number>"; 
   Abstract = TRUE ; 
   Sealed = TRUE; 
   Instantiable = FALSE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new type ;
}

