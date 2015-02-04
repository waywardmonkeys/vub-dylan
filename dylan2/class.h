
/*
 +------------------------------------------------------------------
 | FILENAME  : class.h
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Definitie van een klasse.
 |             Deze bevat de zelf gedefinieerde klassen in dylan
 |             de systeemklassen zitten in object.h
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _CLASS
#define _CLASS
#include "types.h"
#include "list.h"
#include "expression.h"
#include "class_type.h"

class DylanClass : public Constituent
{
   private :
      DylanObject *AClass ;
   public :
      DylanClass( DylanObject *AnObj ) { AClass = AnObj ; }
      void Print( int *i ) { AClass->Print(i) ; } 
      DylanObject *GetValue(Environment *) { return NULL ; }
      void ReEval(Environment *) {}
} ;
/*
 +------------------------------------------------------------
 | Definitie van de klasse dictionnary
 +------------------------------------------------------------
*/

class ClassDictionnary
{
   private:
        struct ClassStruct
        {
            DylanObject *Class ;
            ClassStruct *prev ;
            ClassStruct *next ;
        } ;

        struct ClassList
        {
           ClassStruct *AList ;
           int  Scope ;
           ClassList *prev ;
           ClassList *next ;
        } ;        

        struct ClassList   *TopOfList ;
        struct ClassStruct *PtrClass ;
        void CreateDefaultClasses() ;
        void MakeClass( DylanObject *) ;

   public:
      ClassDictionnary() ;     
      void InsertClass( DylanObject *C) ;
      DylanObject *GetClass() ;
      int   SearchClass( const char *Name ) ;
      void Dump() ;
} ;
#endif
