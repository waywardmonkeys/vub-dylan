#include "range.h"
#include "keyword.h"
#include <string.h>

/*
 +------------------------------------------------------------------
 | FUNCTION  : range::range
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een range
 | DATE      :
 |
 | ABSTRACT  : Constructor voor een range (een range is een set van
 |             getallen )
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
range::range() 
{ 
   id = "<range>"; 
   from = 0.0 ;
   to = 0.0 ;
   above = 0.0 ;
   below = 0.0 ;
   size = 0 ;
   by = 1.0 ;
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new sequence ; 
}
              
/*
 +------------------------------------------------------------------
 | FUNCTION  : range::GetElement
 | INPUT     : int : Ide element
 | OUTPUT    : -
 | RETURN    : een getal
 | DATE      :
 |
 | ABSTRACT  : Ophalen van het ide element.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *range::GetElement( int i )
{ 
   local = i * by + from ; 

   if ( below != 0.0 && local > below ) local = below ;

   if ( above != 0.0 && local < above ) local = above ;

   if (i > size && size != 0 ) local = 0.0 ;

   return new double_float( local );  
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Setter
 | INPUT     : double : ignored
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : In een range kan men de waarden niet wijzigen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void range::Setter( double x ) 
{ 
   printf( "error : not applicable\n" ) ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : range::Instance
 | INPUT     : 
 | OUTPUT    :
 | RETURN    :
 | DATE      :
 |
 | ABSTRACT  : Maken van een instance van een range  
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *range::Instance(DylanObject *X, List<DylanObject *> *InitList )
{
  static DylanObject *O ;

  if ( InitList != NULL )
  {
     O = new range( NULL, InitList )  ;
  }
  else
  {
    O = new range ;
  }
  return O ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : range::range
 | INPUT     : int : een dummy
 |             List<DylanObject *> : initialisatie keyworden
 | OUTPUT    : -
 | RETURN    : een range
 | DATE      :
 |
 | ABSTRACT  : creatie van een range met init keywords, deze keywords
 |             zijn :
 |             from, to, below, above, size, by
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
range::range( int *dummy, List<DylanObject *> *InitList )
{ 
   int i ;
   char str[255] ;

   id = "<range>";
   from = 0 ;
   by = 1 ;
   above = 0 ;
   below = 0 ;
   size  = 0 ;

   for( i = 1; i <= InitList->GetSize(); i++ )
   {
     InitList->MoveTo(i) ;
     InitList->GetItem()->Getter(str) ;
     if ( strcmp( str, "from:" ) == 0 )
     {
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&from) ;
     }
     else if ( strcmp( str, "to:" ) == 0 )
     {
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&to) ;
     }
     else if ( strcmp( str, "above:" ) == 0 )
     {
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&above) ;
     }
     else if ( strcmp( str, "below:" ) == 0 )
     {
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&below) ;
     }
     else if ( strcmp( str, "by:" ) == 0 )
     {
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&by) ;
     }
     else if ( strcmp( str, "size:" ) == 0 )
     {
        ((keyword *) InitList->GetItem())->GetValue(NULL)->Getter(&size) ;
     }
     else error( "Invalid keyword supplied to range !" ) ;

   }
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   Superclass = new DylanObject * [1] ;
   Superclass[0] = new sequence ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : operator==
 | INPUT     : een range
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : test of 2 ranges gelijk zijn (ttz identieke keywords
 |             getallen )
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int range::operator==( const DylanObject *X )
{
   return( (this->from  == ((range *) X)->from) &&
           (this->by    == ((range *) X)->by) &&
           (this->above == ((range *) X)->above) &&
           (this->below == ((range *) X)->below) &&
           (this->size  == ((range *) X)->size) ) ;
}
