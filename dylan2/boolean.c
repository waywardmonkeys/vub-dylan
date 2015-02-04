#include "boolean.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : boolean_type::boolean_type()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een boolean type 
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : geeft een instance terug van een boolean.
 |             (dit is de default constructor)
 | CHANGES   :
 +------------------------------------------------------------------
 */
boolean_type::boolean_type() 
{ 
   id = "<boolean>"; 
   i = FALSE ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new type ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : boolean_type::boolean_type()
 | INPUT     : boolean
 | OUTPUT    : 
 | RETURN    : boolean object
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : deze constructor returnt een false of een true
 |             object.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
boolean_type::boolean_type(int x) 
{ 
   i = x ; 
   id = "<boolean>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new type ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Setter
 | INPUT     : int : een boolean waarde
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Met deze functie kunnen we de interne representatie
 |             van een boolean object wijzigen. Het is de verantwoordelijkheid
 |             van de caller om te zien of dat wat meegegeven wordt wel een
 |             0 of een 1 is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void boolean_type::Setter(int s) 
{ 
   i = s ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : boolean_type::Getter
 | INPUT     : -
 | OUTPUT    : int : de waarde vah het object
 | RETURN    : -
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Deze idiocrasie, die we hier moeten gebruiken is
 |             een limitatie van C++, omdat we geen virtuele functies
 |             kunnen met hetzelfde argumenttype maar verschillend
 |             return type.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void boolean_type::Getter(int *s) 
{ 
   *s = i ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : boolean_type::Print
 | INPUT     : int * : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Pretty print van een boolean
 |             0 = #f
 |             1 = #t
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void boolean_type::Print(int *) 
{
   if ( i )
   {
      printf( "#t") ;
   }
   else 
   {
      printf( "#f") ;
   }  
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : boolean_type::operator==
 | INPUT     : DylanObject * : een boolean
 | OUTPUT    : 
 | RETURN    : TRUE : booleans gelijk
 |             FALSE : booleans niet gelijk
 | DATE      :
 |
 | ABSTRACT  : waarde v.d. booleans vergelijken.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
int boolean_type::operator==( const DylanObject *X )
{
   return( this->i == ((boolean_type *) X)->i ) ;
}
