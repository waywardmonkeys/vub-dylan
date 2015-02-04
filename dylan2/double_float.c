#include "double_float.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : double_float::double_float
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : instance van een double float object
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
double_float::double_float() 
{ 
   id = "<double-float>"; 
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
 | FUNCTION  : double::double_float
 | INPUT     : float  : initialisatie waarde
 | OUTPUT    : -
 | RETURN    : instance van een double float met een waarde
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
double_float::double_float(float x) 
{ 
  i = x ; 
  id = "<double-float>"; 
  Abstract = FALSE ; 
  Sealed = TRUE; 
  Instantiable = TRUE ; 
  NbrSuperclasses = 1 ;
  Superclass = new (GC) DylanObject * [1] ;
  Superclass[0] = new myfloat ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : double_float::Setter
 | INPUT     : double : een double float
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Veranderen van de waarde van een double float object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void double_float::Setter(double s) 
{ 
   i = s ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : double_float::Getter
 | INPUT     : -
 | OUTPUT    : double : de inhoud van een double float
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de interne waarde double-float
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void double_float::Getter(double *s) 
{ 
   *s = i ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : double_float::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void double_float::Print(int *) 
{
   printf( "%lf", i) ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : DylanObject * : double_float object
 | OUTPUT    : TRUE  : getallen gelijk
 |             FALSE : getallen niet gelijk 
 | RETURN    :
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int double_float::operator==( const DylanObject *X )
{
   return( this->i == ((double_float *) X)->i ) ;
}
