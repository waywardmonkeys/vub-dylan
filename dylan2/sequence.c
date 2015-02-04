#include "sequence.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : sequence::sequence
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een sequence
 | DATE      :
 |
 | ABSTRACT  : Constructor van een sequence
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
sequence::sequence() 
{ 
   id = "<sequence>"; 
   Abstract = TRUE ; 
   Sealed = FALSE; 
   Instantiable = FALSE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new collection ; 
} 
