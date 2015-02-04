#include "extended_float.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : extended_float::extended_float
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een extended float
 | DATE      :
 |
 | ABSTRACT  : Default constructor voor extended floats,
 |             Opmerking : intern worden alle soorten floats
 |             voorgesteld als doubles
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
extended_float::extended_float() 
{ 
   id = "<extended-float>"; 
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
 | FUNCTION  : extended_float::extended_float
 | INPUT     : float : initialisatie
 | OUTPUT    : -
 | RETURN    : een extended float object
 | DATE      :
 |
 | ABSTRACT  : 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
extended_float::extended_float(float x) 
{ 
  i = x ; 
  id = "<extended-float>"; 
  Abstract = FALSE ; 
  Sealed = TRUE; 
  Instantiable = TRUE ; 
  NbrSuperclasses = 1 ;
  Superclass = new (GC) DylanObject * [1] ;
  Superclass[0] = new myfloat ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : extended_float::Setter
 | INPUT     : double : een floating point
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van de interne representatie van een extended
 |             float
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void extended_float::Setter(double s) 
{ 
   i = s ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : extended_float::Getter
 | INPUT     : -
 | OUTPUT    : double : ophalen waarde van een extended float
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void extended_float::Getter(double *s) 
{ 
   *s = i ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : extended_float::Print
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
void extended_float::Print(int *) 
{
   printf( "%lf", i) ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : extended_float::operator==
 | INPUT     : 2 floats
 | OUTPUT    : -
 | RETURN    : boolean, TRUE als 2 floats gelijk
 | DATE      :
 |
 | ABSTRACT  : Testen op gelijkheid van 2 floats
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int extended_float::operator==( const DylanObject *X )
{
   return( this->i == ((extended_float *) X)->i ) ;
}
