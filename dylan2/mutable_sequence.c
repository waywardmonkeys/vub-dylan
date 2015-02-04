#include "mutable_sequence.h"
     
/*
 +------------------------------------------------------------------
 | FUNCTION  : mutable::sequence
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een mutable sequence
 | DATE      :
 |
 | ABSTRACT  : Constructor van een mutable sequence
 |             mutable sequences is een superklasse voor lijsten
 |             arrays en vectoren
 | CHANGES   :
 +------------------------------------------------------------------
 */
mutable_sequence::mutable_sequence()  
{ 
   id = "<mutable-sequence>"; 
   Abstract = TRUE ; 
   Sealed = FALSE; 
   Instantiable = FALSE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new sequence ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : mutable_sequence::GetDimensions
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : List<DylanObject *>
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de dimensies van een mutable sequence
 |             (in werkelijkheid zal dit een vector of een array 
 |             zijn).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
List<DylanObject *> *mutable_sequence::GetDimensions()
{ 
   return Dimensions ;
}

