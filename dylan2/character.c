#include "character.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : character::character
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een character object
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : default constructor voor het character type.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
character::character() 
{ 
   id = "<character>"; 
   c = 0 ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : character::character
 | INPUT     : char : een bepaald ASCII character
 | OUTPUT    : - 
 | RETURN    : characterobject geinitialiseerd met s
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Alle karakterobjecten zijn ASCII, (volgens de 
 |             Dylan specificaties moet de UNICODE set ook gesupporteerd zijn )
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
character::character(char s)
{ 
   c = s ;
   id = "<character>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : character::Setter
 | INPUT     : char s : een karakter
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Wijzigen van een character object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void character::Setter(char s)
{   
   c = s ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : character::Getter
 | INPUT     : char * : ontvanger van het karakter
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Ophalen van het karakter uit een karakterobject
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void character::Getter(char *s) 
{ 
   *s = c ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : character::Print
 | INPUT     : int * : indent , niet van toepassing
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Pretty printer
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void character::Print(int *) 
{
   printf( "%c", c) ;
}  


/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : een karakter object
 | OUTPUT    : -
 | RETURN    : TRUE : karakters gelijk
 |             FALSE : karakters ongelijk
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : test of 2 karakters gelijk zijn ( interne representatie)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int character::operator==( const DylanObject *X )
{
   return( this->c == ((character *) X)->c ) ;
}
