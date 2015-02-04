#include "symbol.h"
#include <string.h>

/*
 +------------------------------------------------------------------
 | FUNCTION  : symbol::symbol
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : symbol object
 | DATE      :
 |
 | ABSTRACT  : Constructor van symbol objecten
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
symbol::symbol()
{ 
   id = "<symbol>"; 
   s = "" ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : symbol::symbol
 | INPUT     : const char * : een symbool
 | OUTPUT    : -
 | RETURN    : symbol object
 | DATE      :
 |
 | ABSTRACT  : Constructor van symbol objecten met default waarde
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
symbol::symbol(const char *str)
{ 
   s = str ;
   id = "<symbol>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : symbol::Setter
 | INPUT     : const char * : een symbool
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Veranderen van een symbool object
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void symbol::Setter(const char *str)
{ 
   s = str ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : symbol::Getter
 | INPUT     : -
 | OUTPUT    : char * 
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de waarde van een symbool object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void symbol::Getter(char *str) 
{ 
   strcpy(str , s); 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : symbol::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : pretty printer van een symbool
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void symbol::Print(int *) 
{
   printf( "%s", s) ;
}  

