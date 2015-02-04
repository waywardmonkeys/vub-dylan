#include "single_float.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : single_float::single_float
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een single float
 | DATE      :
 |
 | ABSTRACT  : Constructor van een single float
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
single_float::single_float() 
{ 
   id = "<single-float>"; 
   i = 0.0 ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new myfloat ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : single_float::single_float
 | INPUT     : float : een reeel getal
 | OUTPUT    : -
 | RETURN    : single_float object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een single float met initiele
 |             waarde
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
single_float::single_float(float x) 
{ 
   i = x ; 
   id = "<single-float>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new myfloat ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : single_float::Setter
 | INPUT     : float : een reeel getal
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van de interne representatie van een 
 |             single float object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void single_float::Setter(float s) 
{  
   i = s ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : single_float::Getter
 | INPUT     : -
 | OUTPUT    : float : de interne representatie van een float
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de interne representatie van een 
 |             single float.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void single_float::Getter(float *s) 
{ 
  *s = i ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : single_float::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een float
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void single_float::Print(int *) 
{
   printf( "%f", i) ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : een float
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : testen of 2 single_float objecten gelijk zijn.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int single_float::operator==( const DylanObject *X )
{
   return( this->i == ((single_float *) X)->i ) ;
}
