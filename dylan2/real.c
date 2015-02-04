#include "real.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : real::real
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een real
 | DATE      :
 |
 | ABSTRACT  : Constructor van een real 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
real::real() 
{ 
   id = "<real>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new number ; 
}
