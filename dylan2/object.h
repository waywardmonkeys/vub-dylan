/*
 +------------------------------------------------------------------
 | FILENAME  : object.h
 | DATE      : 01/12/1994
 |
 | ABSTRACT  : voorgedefinieerde dylan klassen
 |             Deze file bevat de klassen zoals voorgesteld in 
 |             de DIRM manual. 
 |             Op dit moment zijn nog niet alle systeemklassen
 |             geimplementeerd.
 |             
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _OBJECT
#define _OBJECT
#include "types.h"
#include "list.h"
#include "property.h"
#include <stdio.h>
#include "slot.h"
class Slot_specs ;
class Environment ;
class DylanObject : public gc
{
   protected :
     const char   *id ;
     Boolean       Abstract ;
     Boolean       Sealed ;
     Boolean       Instantiable ;
     DylanObject **Superclass ;
     int           NbrSuperclasses ;
     DylanObject  *ClassPrecedenceList[255] ;
     int           NbrClasses ;

     void TSort( DylanObject * ) ;

  public :
     /* constructor */
     DylanObject()  ;

     const char          *GetName();
     DylanObject         *GetValue(Environment *);
     DylanObject        **GetDirectSuperclass(int *classes );
     DylanObject        **GetSuperclass(int *classes );
     int                  ReturnNbrSuperclasses();

     virtual void                 Print(int *) {;}
     virtual int                  operator==( const DylanObject *X)  { return FALSE ; }
     virtual Slot_specs          *ReturnSlot(const char *) {return NULL ;}
     virtual List<Slot_specs *>  *GetSlots() {return NULL ;}
     virtual int                  ReturnParaType() { return normal ; }

     /* setter functions */
     virtual void                 Setter(char ) {} 
     virtual void                 Setter(long ) {}
     virtual void                 Setter(const char *) {}
     virtual void                 Setter(float) {}
     virtual void                 Setter(double) {} 
     virtual void                 Setter(int, DylanObject *) {} 
 
     /* getter functions */
     virtual void                 Getter(int * ) {} 
     virtual void                 Getter(long * ) {}
     virtual void                 Getter(char *) {}
     virtual void                 Getter(float *) {}
     virtual void                 Getter(double *) {} 
     virtual void                 Getter(int , double *) {} 
     virtual DylanObject         *GetElement(int) { return NULL ; } 
     virtual void                 Getter(List<DylanObject *> *) {} 

     virtual Method              *GetBody() {return NULL ;} 

     virtual void                 Initialize(List<DylanObject *> * ) {} 

     virtual int                  Size() { return 0 ;}
     virtual Boolean              Empty() {return FALSE ;}
     virtual Boolean              IsAbstract() {return Abstract ;}
     virtual Boolean              IsInstantiable() { return Instantiable ; }
     virtual DylanObject         *Instance( DylanObject *, List<DylanObject *> * ) { return NULL; }
     virtual List<DylanObject *> *GetDimensions() {return NULL ;}
     virtual void                 SetEnv(Environment *) {}
     virtual Environment         *GetEnv() {return NULL ;}
} ;

extern long MakeInteger( const char *s ) ;
extern double MakeReal( const char *s ) ;
#endif
