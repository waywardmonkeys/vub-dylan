#include "array.h"
#include "keyword.h"
#include <string.h>

/*
 +------------------------------------------------------------------
 | FUNCTION  : array()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een instance van het type array
 | DATE      :
 |
 | ABSTRACT  : constructor voor het array type.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
array::array() 
{ 
   id = "<array>"; 
   Internal = NULL ;   
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : GetElement
 | INPUT     : int i : index in de array.
 | OUTPUT    : -
 | RETURN    : DylanObject, het gevraagde element uit de array
 | DATE      :
 |
 | ABSTRACT  : Getter van het ide element uit een array
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *array::GetElement(int i ) 
{ 
    return Internal[i] ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Setter
 | INPUT     : index : positie binnen de array
 |             *Obj  : het element dat men op die positie wenst
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Inbrengen van een object in een array.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void array::Setter(int index, DylanObject *Obj )
{ 
  Internal[index] = Obj ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Empty
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : #t = array is leeg
 |             #f = array is niet leeg
 | DATE      :
 |
 | ABSTRACT  : Een array wordt als leeg beschouwd zolang er nog
 |             geen instance van is gecreeerd.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean array::Empty() 
{ 
   return ( Internal == NULL ) ; 
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Instance
 | INPUT     : DylanObject : object van het type array
 |             List<DylanObject *> : initialisatie parameters
 | OUTPUT    : 
 | RETURN    : een instance van een array.
 | DATE      :
 |
 | ABSTRACT  : Creatie van een instance, het dylanobject dat
 |             meegegeven wordt heeft hier geen belang omdat
 |             we weten over welk type object het gaat.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *array::Instance(DylanObject *X, List<DylanObject *> *InitList )
{
  static DylanObject *O ;

  if ( InitList != NULL )
  {
     O = new array( NULL, InitList )  ;
  }
  else
  {
    O = new array ;
  }
  return O ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : array()
 | INPUT     : dummy : een dummy pointer.
 |             List<DylanObject *> : initialisatie parameters
 | OUTPUT    : -
 | RETURN    : een instance v.e. array
 | DATE      :
 |
 | ABSTRACT  : Creatie van een array.
 |             de volgende initialisatie parameters zijn toegestaan:
 |             dimensions: de dimensies van de array.
 |             fill: de default waarde van de array.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
array::array( int *dummy, List<DylanObject *> *InitList )
{ 
   int i ;
   int j ;
   char str[255] ;
   long index ;
   long maxsize ;
   id = "<array>";

   for( i = 1; i <= InitList->GetSize(); i++ )
   {
     InitList->MoveTo(i) ;
     InitList->GetItem()->Getter(str) ;
     if ( strcmp( str, "dimensions:" ) == 0 )
     {
        Dimensions = new List<DylanObject *> ;
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(Dimensions) ;
        maxsize = 1 ;
        for( j = 1; j <= Dimensions->GetSize(); j++ )
        {
           Dimensions->MoveTo(j) ;
           Dimensions->GetItem()->Getter(&index) ;
           maxsize = maxsize * index ; 
        }
        Internal = new DylanObject * [maxsize] ;
        for( j = 0; j < maxsize; j++ )
        {
            Internal[j] = false_object ;
        }
     }
     if ( strcmp( str, "fill:" ) == 0 )
     {
        for( j = 0; j < maxsize; j++ )
        {
            Internal[j] = ((keyword *) InitList->GetItem())->GetValue(NULL) ;
        }
     }
   }

   Abstract = FALSE ;
   Sealed = FALSE ;
   Instantiable = TRUE ; 
   Superclass = new DylanObject * [1] ;
   Superclass[0] = new mutable_sequence ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Afprinten van een array.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void array::Print( int *x ) 
{
  int j ;
  int i ;
  long maxsize ;
  long index ;

  printf( "#[ ") ;
  maxsize = 1 ;
  for( i = 1 ; i <= Dimensions->GetSize(); i++ )
  {
    Dimensions->MoveTo(i) ;
    Dimensions->GetItem()->Getter(&index) ;
    maxsize = maxsize * index ;
  }

  for( j = 0; j < maxsize; j++ )
  {
     Internal[j]->Print(x) ;
     if ( j != maxsize ) printf(", ") ;
  }
  printf( " ]" ) ;
}


/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : DylanObject*
 | OUTPUT    :
 | RETURN    : TRUE  : objecten zijn gelijk
 |             FALSE : objecten zijn niet gelijk
 | DATE      : 01/01/95
 |
 | ABSTRACT  : Testen of 2 arrays gelijk zijn (deep)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int array::operator==( const DylanObject *X )
{
   int j ;
   int i ;
   long maxsize ;
   long index ;

   if ( this->Dimensions->GetSize() !=
        ((array *) X)->Dimensions->GetSize() ) return FALSE ;


   maxsize = 1 ;
   for( i = 1 ; i <= this->Dimensions->GetSize(); i++ )
   {
     this->Dimensions->MoveTo(i) ;
     this->Dimensions->GetItem()->Getter(&index) ;
     maxsize = maxsize * index ;
   }

   for( j = 0; j < maxsize; j++ )
   {
      if ( this->Internal[j] != ((array *) X)->Internal[j] ) 
          return FALSE  ;
   }
   return TRUE ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : array::Size
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Grootte van de array
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Een array is multi-dimensionaal, dus optellen en
 |             vermenigvuldigen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int array::Size()
{
   long maxsize ;
   long index ;
   int i ;

   maxsize = 1 ;
   for( i = 1 ; i <= Dimensions->GetSize(); i++ )
   {
     Dimensions->MoveTo(i) ;
     Dimensions->GetItem()->Getter(&index) ;
     maxsize = maxsize * index ;
   }
   return maxsize ;
}
