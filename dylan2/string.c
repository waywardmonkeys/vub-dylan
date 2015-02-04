#include "string.h"
#include "character.h"
#include "keyword.h"
#include <string.h>

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::string
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : string
 | DATE      :
 |
 | ABSTRACT  : Constructor van een string object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
string::string() 
{ 
   id = "<string>"; 
   s = strdup("") ;
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::string
 | INPUT     : const char * : een string
 | OUTPUT    : -
 | RETURN    : een string object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een string object met default
 |             waarde
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
string::string(const char *str) 
{ 
   // XXX
   s = strdup(str) ;
   id = "<string>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::Setter
 | INPUT     : const char * : een string
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van een string object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void string::Setter(const char *str) 
{ 
   s = strdup(str) ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::Getter
 | INPUT     : -
 | OUTPUT    : char * : een string
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de karakterstring uit een string
 |             object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void string::Getter(char *str) 
{ 
   strcpy(str , s) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer voor strings
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void string::Print(int *) 
{
   char *str ;
   str = new (GC) char [255] ; 
   strcpy( str, s ) ;
   if ( str[0] == '"' ) str = (str + 1) ;
   if (str[strlen(str) - 1] == '"' ) str[strlen(str) - 1] = '\0' ;

   printf( "%s", str) ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : string : een string object
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : test of 2 string objects gelijk zijn.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int string::operator==( const DylanObject *X )
{
   return( strcmp(this->s , ((string *) X)->s) == 0) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::GetElement
 | INPUT     : int : index 
 | OUTPUT    : -
 | RETURN    : character
 | DATE      :
 |
 | ABSTRACT  : Uit een string het ide karakter halen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *string::GetElement( int i )
{
   return new character( s[i] ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::Instance
 | INPUT     : DylanObject : ignored
 |             List<DylanObject *> : initialisatie argumenten
 | OUTPUT    : -
 | RETURN    : een string object
 | DATE      :
 |
 | ABSTRACT  : Instantiëren van een string object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *string::Instance(DylanObject *X, List<DylanObject *> *InitList )
{
  static DylanObject *O ;

  if ( InitList != NULL )
  {
     O = new string( NULL, InitList )  ;
  }
  else
  {
    O = new string ;
  }
  return O ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : string::string
 | INPUT     : List<DylanObject *> : initialisatie argumenten
 | OUTPUT    : -
 | RETURN    : string object
 | DATE      :
 |
 | ABSTRACT  : Constructor voor strings met een initialisatielijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
string::string( int *dummy, List<DylanObject *> *InitList )
{ 
   int i ;
   char str[255] ;
   int size ;
   id = "<string>";

   InitList->MoveTo(1) ;
   InitList->GetItem()->Getter(str) ;
   if ( strcmp( str, "size:" ) == 0 )
   {
      ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&size) ;
   }
   s = new char [size + 1] ;
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   Superclass = new DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Setter
 | INPUT     : int  : plaats in de string
 |             DylanObject : een karakter
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van het ide karakter in een string
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void string::Setter(int index, DylanObject *Obj ) 
{
   char ch ;
   Obj->Getter(&ch) ;
   s[index] = ch ;
}
