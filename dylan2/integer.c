#include "integer.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : integer::integer
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een integer
 | DATE      :
 |
 | ABSTRACT  : Constructor voor de creatie van een integer object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
integer::integer() 
{ 
   id = "<integer>"; 
   i = 0 ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new real ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : integer::integer
 | INPUT     : long : een integer waarde
 | OUTPUT    : -
 | RETURN    : een integer object
 | DATE      :
 |
 | ABSTRACT  : Constructor voor de creatie van een integer object
 |             Merk op dat we als integers 32bit getallen nemen
 |             volgens de specificatie van Dylan moeten integers
 |             minstens 28bit zijn.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
integer::integer(long x) 
{ 
   i = x ; 
   id = "<integer>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new real ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Setter
 | INPUT     : long : een integer
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van een integer object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void integer::Setter(long s) 
{ 
   i = s ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : integer::Getter
 | INPUT     : -
 | OUTPUT    : long * : interne representatie 
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de interne representatie van een int
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void integer::Getter(long *s) 
{ 
  *s = i ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : integer::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een int
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void integer::Print(int *) 
{
  printf( "%ld", i) ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : integer::Instance
 | INPUT     : DylanObject : ignored
 |             List<DylanObject *> : ignored
 | OUTPUT    : -
 | RETURN    : een integer object
 | DATE      :
 |
 | ABSTRACT  : Instantiatie van een integer object (voor de make
 |             functie call)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *integer::Instance( DylanObject *, List<DylanObject *> * ) 
{ 
  return new integer ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : DylanObject : een object
 | OUTPUT    : -
 | RETURN    : TRUE  : objecten zijn gelijk
 |             FALSE : objecten zijn niet gelijk
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int integer::operator==( const DylanObject *X )
{
   return( this->i == ((integer *) X)->i ) ;
}
