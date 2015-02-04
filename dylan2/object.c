/*
 +------------------------------------------------------------------
 | FILENAME  : object.c
 | DATE      : 10/12/1994
 |
 | ABSTRACT  : Moederfile van alle Dylanobjecten
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include "object.h"
#include "expression.h"
#include <string.h>
#include <stdio.h>

/*
 +------------------------------------------------------------------
 | FUNCTION  : MakeInteger
 | INPUT     : char : een string met een integer
 | OUTPUT    : -
 | RETURN    : een integer (long)
 | DATE      : 10/12/1994
 |
 | ABSTRACT  : Deze functie converteert een string naar een
 |             getal. Deze string kan een hexadecimaal, octaal of
 |             decimaal getal zijn.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
long MakeInteger( char *s )
{
   long AnInt ;
   int i ;
   int Mul ;

   if ( strncmp( s, "#x", 2) == 0 )
   {
      sscanf( s + 2, "%lx", &AnInt ) ;
   }
   else if ( strncmp( s, "#o", 2) == 0 )
   {
      sscanf( s + 2, "%lo", &AnInt ) ;
   }
   else if ( strncmp( s, "#b", 2) == 0 )
   {
      AnInt = 0 ;
      for ( i = strlen(s) - 1 ; i >= 2 ; i-- )
      {
         Mul = 2 << (strlen(s) - i - 2) ;
         Mul = (Mul == 0) ? 1 : Mul ; 
         AnInt += (s[i] - '0') * Mul ;
      }
   }
   else
   {
      sscanf( s, "%ld", &AnInt ) ;
   }
   return AnInt ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MakeReal
 | INPUT     : char : een real string
 | OUTPUT    : -
 | RETURN    : een floating point getal
 | DATE      :
 |
 | ABSTRACT  : Deze functie vormt een string om naar een double
 |             Op dit moment worden enkel reals als double
 |             gesupporteerd.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
double MakeReal( char *s )
{
   double AReal ;

   sscanf( s, "%lf", &AReal ) ;
   return AReal ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::TSort
 | INPUT     : DylanObject : een object
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 22/12/1994
 |
 | ABSTRACT  : Deze functie berekent een topologische sort van 
 |             de classes van een DylanObject.
 |             Wordt gebruikt om te weten van welke superclassen
 |             dit object allemaal erft.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void DylanObject::TSort( DylanObject *x ) 
{
   int i ;
   int j ;
   DylanObject **s ;
   int ok ;
   int Size ;

   /* class precedence list already computed */

   if ( ClassPrecedenceList[0] != NULL ) return ; 
   s = x->GetDirectSuperclass(&Size) ;
   if ( s[0] == NULL ) 
   {
      ok = 1 ;
      for( j = 0; j < NbrClasses; j++ )
      {
          if ( strcmp( ClassPrecedenceList[j]->GetName(), x->GetName()) == 0 ) ok = 0 ;
      }
      if (ok) ClassPrecedenceList[NbrClasses++] = x ;
      return ;
   }
   for( i = Size - 1; i >= 0 ;  i-- )
   {
       TSort(s[i] ) ;
   }
   ok = 1 ;
   for( j = 0; j < NbrClasses; j++ )
   {
      if ( strcmp( ClassPrecedenceList[j]->GetName(), x->GetName()) == 0 ) ok = 0 ;
   }
   if (ok) ClassPrecedenceList[NbrClasses++] = x ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::DylanObject
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Instantiatie van een het element <object>
 | DATE      :
 |
 | ABSTRACT  : Het type <object> is de moeder van alle objecten.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject::DylanObject()  
{ 
   id = "<object>"; 
   Abstract = TRUE ; 
   Sealed = TRUE; 
   Instantiable = FALSE ; 
   NbrClasses = 0 ;
   NbrSuperclasses = 1 ;
   ClassPrecedenceList[0] = NULL ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::GetName
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : naam van het object
 | DATE      :
 |
 | ABSTRACT  : ophalen van de naam van het object (= het type)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
char *DylanObject::GetName()
{
   return id ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::GetValue
 | INPUT     : Environment *
 | OUTPUT    : -
 | RETURN    : NULL
 | DATE      :
 |
 | ABSTRACT  : Dit is een virtuele functie, het zijn de afstammelingen
 |             die iets moeten doen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *DylanObject::GetValue(Environment *Env)
{
    return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::GetDirectSuperclass
 | INPUT     : -
 | OUTPUT    : int : aantal directe superclassen
 | RETURN    : Een object
 | DATE      :
 |
 | ABSTRACT  : Deze functie retourneert alle directe superclassen
 |             van een bepaald object.
 |             Enkel de directe, niet de superklassen van de super-
 |             klassen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject **DylanObject::GetDirectSuperclass(int *classes )
{ 
      *classes = NbrSuperclasses ;
      return Superclass ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::GetSuperclass
 | INPUT     : -
 | OUTPUT    : int : totaal aantal superclasses.
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Geeft ALLE superclassen terug van een bepaald
 |             object.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject **DylanObject::GetSuperclass(int *classes )
{ 
   TSort(this) ;
   *classes = NbrClasses ;
   return ClassPrecedenceList ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : DylanObject::ReturnNbrSuperclasses
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Aantal directe superclasses.
 | DATE      : 
 |
 | ABSTRACT  : Geeft het aantal directe superclasses.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int DylanObject::ReturnNbrSuperclasses()
{
  return NbrSuperclasses ;
}
