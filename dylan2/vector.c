#include "vector.h"
// de support voor vectoren is nog niet voor 100% klaar,
// met name de voorwaarde dat een vector een 1dimensionale
// structuur wordt niet getest.
/*
 +------------------------------------------------------------------
 | FUNCTION  : vector::vector
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een vector object
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : default constructor voor een vector
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
vector::vector() 
{ 
   id = "<vector>"; 
   Internal = NULL ;   
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new array ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : vector::vector
 | INPUT     : List<DylanObject * > * : een vector
 | OUTPUT    : -
 | RETURN    : een vector, met reeds geinitialiseerde elementen
 | DATE      :
 |
 | ABSTRACT  : Copy constructor van vectoren
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
vector::vector(List<DylanObject *> *l ) 
{ 
   id = "<vector>"; 
   Internal = l ;   
   Abstract = FALSE ; 
   Sealed = FALSE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new array ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : vector::Getter
 | INPUT     : -
 | OUTPUT    : De complete vector wordt teruggeven
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Er weze opgemerkt dat vectoren geimplementeerd
 |             zijn als lineaire lijsten.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void vector::Getter(List<DylanObject *> *l ) 
{ 
   *l = *Internal ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : vector::Size() 
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Groote van de vector
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int vector::Size() 
{ 
   return Internal->GetSize() ; 
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  :  vector::Empty
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : TRUE : vector is leeg
 |             FALSE = vector niet leeg
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean vector::Empty() 
{ 
   return ( Internal ->GetSize() == 0 ) ; 
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : vector::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een vector
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void vector::Print( int *i ) 
{
  int j ;
  printf( "#[ ") ;
  for( j = 1; j <= Internal->GetSize(); j++ )
  {
     Internal->MoveTo(j) ;
     Internal->GetItem()->Print(i) ;
     if ( j != Internal->GetSize() ) printf(", ") ;
  }
  printf( " ]" ) ;
}
DylanObject *vector::GetElement(int i ) 
{ 
  Internal->MoveTo(i + 1) ;
  return Internal->GetItem() ;
}
void vector::Setter(int index, DylanObject *Obj )
{ 
   Internal->MoveTo(index + 1) ;
   Internal->UpdateItem( Obj ) ;
}
