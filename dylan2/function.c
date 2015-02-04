#include "function.h"
#include "method.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::function
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Een functie object
 | DATE      :
 |
 | ABSTRACT  : Default constructor voor een functie object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
function::function( ) 
{ 
  id = "<function>";
  fct = ""; 
  Abstract = FALSE ; 
  Sealed = TRUE; 
  Instantiable = TRUE ; 
  NbrSuperclasses = 1 ;
  Superclass = new (GC) DylanObject * [1] ;
  Superclass[0] = new DylanObject ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::function
 | INPUT     : char * : naam van de functie
 | OUTPUT    : -
 | RETURN    : een functie object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een functieobject met een bepaalde
 |             naam.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
function::function( char *s ) 
{ 
   id = "<function>";
   fct = s ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::function
 | INPUT     : Method * : een methode
 | OUTPUT    : -
 | RETURN    : een functieobject
 | DATE      :
 |
 | ABSTRACT  : Creatie van een functieobject met een body
 |             (= anonieme methoden of lambda's )
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
function::function( Method *B ) 
{ 
   id = "<function>";
   fct = NULL ;
   fct_body = B ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::Setter
 | INPUT     : char *   : naam van de functie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Naam geven aan een functie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void function::Setter(char *s) 
{ 
   fct = s ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::Getter
 | INPUT     : -
 | OUTPUT    : char *  : naam van de functie
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen naam van de functie, indien anonieme 
 |             functies : s = NULL.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void function::Getter(char *s) 
{ 
   if ( fct != NULL )
   {
      strcpy( s , fct) ;
   }
   else
   {
      s = NULL ;
   }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::Print
 | INPUT     : int   : indentatie
 | OUTPUT    : -
 | RETURN    : 
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een functie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void function::Print(int *i) 
{
   int j = 0 ;

   printf ( "%s", fct ) ;
   ((Method *)fct_body)->Print(&j) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::GetBody
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : de body van een functie
 | DATE      :
 |
 | ABSTRACT  : Teruggeven van de body van een functie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Method *function::GetBody() 
{ 
   return ((Method *) fct_body) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::GetEnv
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Environment * : een omgeving
 | DATE      :
 |
 | ABSTRACT  : Teruggeven van de omgeving waarin de functie
 |             moet uitgevoerd worden.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Environment *function::GetEnv()
{
   return Env ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : function::SetEnv
 | INPUT     : Environment * : een omgeving
 | OUTPUT    : -
 | RETURN    : - 
 | DATE      :
 |
 | ABSTRACT  : Toewijzen van een omgeving aan een functie
 |             zodanig dat we later nog weten in welke omgeving 
 |             deze functie moeten uitvoeren
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void function::SetEnv(Environment *E )
{
   Env = E ;
}
