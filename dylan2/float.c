#include "float.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : myfloat::myfloat
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : myfloat
 | DATE      :
 |
 | ABSTRACT  : Creatie van de abstracte klasse voor de 
 |             floating point klassen (abstract voor Dylan)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
myfloat::myfloat() 
{ 
   id = "<float>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new real ; 
}

