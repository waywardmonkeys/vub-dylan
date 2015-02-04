/*
 +------------------------------------------------------------------
 | FILENAME  : class.c
 | DATE      : 01/11/1994
 |
 | ABSTRACT  : Bevat een aantal functies voor het beheer van een
 |             class dictionnary.
 |             In de class dictionnary zelf houden we enkel de pointers
 |             bij naar de actuele klasse.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include <stdio.h>
#include "class.h"
#include "primitive.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : class::GetClass()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Pointer naar een klasse.
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *ClassDictionnary::GetClass() 
{ 
   return TopOfList->AList->Class ;
} ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassDictionnary::MakeClass
 | INPUT     : DylanObject : een klasse
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Deze private functie wordt gebruikt om een aantal
 |             primitive klassen toe te voegen aan het systeem
 |             Deze primitive klassen zij, uiterraard overridable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void ClassDictionnary::MakeClass( DylanObject *o )
{
   if ( TopOfList->AList == NULL )
   {
      TopOfList->AList = new ClassStruct ;
      TopOfList->AList->Class = o;
      TopOfList->AList->next  = NULL ;
      TopOfList->AList->prev  = NULL ;
   }
   else
   {
      TopOfList->AList->next  = new ClassStruct ;
      TopOfList->AList->next->prev  = TopOfList->AList ;
      TopOfList->AList        = TopOfList->AList->next ;
      TopOfList->AList->Class = o ;
      TopOfList->AList->next  = NULL ;
   }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassDictionnary::CreateDefaultClasses
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/01/95
 |
 | ABSTRACT  : Creatie van de primitive klassen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void ClassDictionnary::CreateDefaultClasses()
{

   MakeClass( object_object) ;
   MakeClass( string_object );
   MakeClass( number_object );
   MakeClass( symbol_object );
   MakeClass( real_object );
   MakeClass( float_object );
   MakeClass( s_float_object );
   MakeClass( d_float_object );
   MakeClass( e_float_object );
   MakeClass( rational_object );
   MakeClass( integer_object);
   MakeClass( function_object);
   MakeClass( array_object);
   MakeClass( vector_object);
   MakeClass( list_object);
   MakeClass( collection_object);
   MakeClass( sequence_object);
   MakeClass( mutable_sequence_object);
   MakeClass( range_object);
   MakeClass( class_object);
   MakeClass( type_object);
   MakeClass( boolean_object);
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassDictionnary::ClassDictionnary()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Een nieuwe classdictionnary
 | DATE      :
 |
 | ABSTRACT  : Initialisatie van een klasse dictionnary
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
ClassDictionnary::ClassDictionnary()
{
   TopOfList = new ClassList ;
   TopOfList->next = NULL ;
   TopOfList->prev = NULL ;
   TopOfList->Scope = -1 ; /* system default classes */
   TopOfList->AList = NULL ;
   CreateDefaultClasses() ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassDictionnary::Dump()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Dumpen van de inhoud van een dictionnary,
 |             Voor debugging redenen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void ClassDictionnary::Dump()
{
   struct ClassList   *P ;
   int i ; 
   i = 0 ;

   while ( TopOfList->prev != NULL )
   {
       TopOfList = TopOfList->prev ;
   }
   P = TopOfList ;
   while (TopOfList != NULL ) 
   {
      printf( "Scope level = %d\n", TopOfList->Scope ) ;
      PtrClass = TopOfList->AList ;
      
      while ( PtrClass->prev != NULL )
      {
           PtrClass = PtrClass->prev ;
      }

      while ( PtrClass->next != NULL )
      {
           PtrClass->Class->Print(&i) ;
           PtrClass = PtrClass->next ;
      }
      PtrClass->Class->Print(&i) ;

      TopOfList = TopOfList->next ;
   }
   TopOfList = P ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassDictionnary::InsertClass()
 | INPUT     : DulanObject : een klasse
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Toevoegen van een klasse in de datadictionnary.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void ClassDictionnary::InsertClass( DylanObject *C )
{

    if ( TopOfList->AList != NULL )
    {
       PtrClass = TopOfList->AList ;
       while ( PtrClass->next != NULL )
       {
           PtrClass = PtrClass->next ;
       }
       PtrClass->next = new ClassStruct ;
       PtrClass->next->prev  = PtrClass ;
       PtrClass = PtrClass->next ;
       PtrClass->Class = C ;
       PtrClass->next  = NULL ;
    }
    else
    {
      TopOfList->AList = new ClassStruct ;
      TopOfList->AList->Class = C ;
      TopOfList->AList->next  = NULL ;
      TopOfList->AList->prev  = NULL ;
    }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassDictionnary::SearchClass
 | INPUT     : char * : een klasse
 | OUTPUT    : -
 | RETURN    : TRUE : klasse gevonden !
 |             FALSE : klasse niet gevonden
 | DATE      : 
 |
 | ABSTRACT  : Opzoeken van een klasse gebeurt door de lijst 
 |             sequentieel af te lopen.
 |             Dit is niet het meest intelligente algoritme (aanpassen !)
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
int ClassDictionnary::SearchClass( char *Name )
{
    struct ClassList   *P ;

    while ( TopOfList->next != NULL )
    {
       TopOfList = TopOfList->next ;
    }

    P = TopOfList ;

    while ( TopOfList != NULL )
    {
       PtrClass = TopOfList->AList ;
       while ( TopOfList->AList->prev != NULL )
       { 
           TopOfList->AList = TopOfList->AList->prev ;
       }
       while ( TopOfList->AList != NULL )
       {
           if ( strcmp ( TopOfList->AList->Class->GetName(), Name ) == 0 )
           {
               return TRUE ;
           }
           TopOfList->AList = TopOfList->AList->next ;
       }
       TopOfList->AList = PtrClass ;
       TopOfList = TopOfList->prev ;
    }

    TopOfList = P ;
    return FALSE ;
}
