#include "list_type.h"
#include "keyword.h"
#include <string.h>

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::list
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een lijst object
 | DATE      :
 |
 | ABSTRACT  : Default constructor van een lijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
list::list() 
{ 
   id = "<list>"; 
   Internal = NULL ;   
   Dimensions = NULL ;
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::list
 | INPUT     : List<DylanObject *> : een lijst van objecten
 | OUTPUT    : -
 | RETURN    : een lijst object
 | DATE      :
 |
 | ABSTRACT  : Constructor voor een lijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
list::list(List<DylanObject *> *l ) 
{ 
   id = "<list>"; 
   Dimensions = NULL ;
   if ( l != NULL ) 
   {
      Internal = l ;   
   } 
   else
   {
      Internal = new List<DylanObject *> ;
   }
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::GetElement
 | INPUT     : int : ié element
 | OUTPUT    : -
 | RETURN    : een Object
 | DATE      :
 |
 | ABSTRACT  : Ophalen van het Ide element uit een lijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *list::GetElement(int i ) 
{ 
  Internal->MoveTo(i + 1) ;
  return Internal->GetItem() ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::Getter
 | INPUT     : -
 | OUTPUT    : List<DylanObject *>
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van gans de lijst uit een <list> object
 |             (gebruikt bij het copieren van lijsten)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void list::Getter(List<DylanObject *> *l ) 
{ 
   *l = *Internal ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::Setter
 | INPUT     : int   : de plaats waar we het object gaan plaatsen
 |             DylanObject : het object
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van een element in een lijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void list::Setter(int index, DylanObject *Obj )
{ 
   Internal->MoveTo(index + 1) ;
   Internal->UpdateItem( Obj ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::Size()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : De grootte van de lijst
 | DATE      :
 |
 | ABSTRACT  : Teruggeven van de grootte van de lijst, let op
 |             lijsten in Dylan beginnen te tellen vanaf 0.
 |             Terwijl in de interne representatie een lijst telt
 |             vanaf 0.
 | CHANGES   :
 +------------------------------------------------------------------
 */
int list::Size() 
{ 
   return Internal->GetSize() ; 
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::Empty()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : TRUE : lijst is leeg
 |             FALSE : lijst is niet leeg.
 | DATE      :
 |
 | ABSTRACT  : Test of de lijst al of niet leeg is
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean list::Empty() 
{ 
   return ( Internal ->GetSize() == 0 ) ; 
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een lijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void list::Print( int *i ) 
{
  int j ;
  printf( "#( ") ;
  for( j = 1; j <= Internal->GetSize(); j++ )
  {
     Internal->MoveTo(j) ;
     Internal->GetItem()->Print(i) ;
     if ( j != Internal->GetSize() ) printf(", ") ;
  }
  printf( " )" ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::Instance
 | INPUT     : DylanObject : ignored
 |             List<DylanObject *> : initialisatie parameters
 | OUTPUT    : -
 | RETURN    : een lijst
 | DATE      :
 |
 | ABSTRACT  : Men kan een lijst creëren met bepaalde initialisatie
 |             keywords ( size & fill ).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *list::Instance(DylanObject *X, List<DylanObject *> *InitList )
{
  static DylanObject *O ;

  if ( InitList != NULL )
  {
     O = new list( NULL, InitList )  ;
  }
  else
  {
    O = new list ;
  }
  return O ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : list::list
 | INPUT     : int : een dummy
 |             List<DylanObject *> : initialisatie keywords
 | OUTPUT    : -
 | RETURN    : een lijst
 | DATE      :
 |
 | ABSTRACT  : Constructor met initialisatie argumenten.
 |             Deze argumenten zijn :
 |             fill: default waarden v.d. lijst
 |             size: grootte van de lijst
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
list::list( int *dummy, List<DylanObject *> *InitList )
{
  char str[255] ;
  int  i ;
  long size = 0 ;

  id = "<list>" ;
  Abstract = FALSE ;
  Sealed = FALSE ;
  Instantiable = TRUE ;
  Superclass = new DylanObject * [1] ;
  Superclass[0] = new mutable_sequence ;

  if ( InitList->GetSize() > 2)
  {
    error( "Init arguments for list can only contain size: and fill:") ;
  }

  for( i = 1; i <= InitList->GetSize(); i++ )
  {
     InitList->MoveTo(i) ;
     InitList->GetItem()->Getter(str) ;
     if ( strcmp( str, "size:" ) == 0 )
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&size) ;
     break ;
  }
  if ( InitList->GetSize() == 2 ) 
  {
     InitList->MoveTo(2) ;
     Internal = new List<DylanObject *> ;
     InitList->GetItem()->Getter(str) ;
     if ( strcmp( str, "fill:" ) != 0 )
         error( "Second argument must be the fill: keyword !" ) ;
     for( i = 1; i <= size; i++ )
     {
        Internal->AppendItem( ((keyword *) InitList->GetItem())->GetValue(NULL)) ;
     }
  }
  else
  {
     Internal = new List<DylanObject *> ;
     for( i = 1; i <= size; i++ )
     {
        Internal->AppendItem(false_object) ;
     }
  }
}

