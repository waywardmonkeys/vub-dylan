#include "rational.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : rationale::rational
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een rational
 | DATE      :
 |
 | ABSTRACT  : Constructor van een rational
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
rational::rational() 
{ 
   id = "<rational>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new real ; 
}

