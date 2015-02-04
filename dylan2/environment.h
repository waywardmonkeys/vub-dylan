/*
 +------------------------------------------------------------------
 | FILENAME  : environment.h
 | DATE      : 08/01/1995
 |
 | ABSTRACT  : Implementatie van environments
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef __ENVIRONMENT
#define __ENVIRONMENT
#include "types.h"
#include "object.h"

class Binding : public gc
{
   private:
      Variable *V ;
      DylanObject *O ;
   public:
      Binding( Variable *, DylanObject * ) ;
      Variable *GetVariable() ;
      DylanObject *GetObject() ;
      void SetObject( DylanObject *Obj ) { O = Obj ; }
      void Print(int *) {}
} ;

class Environment : public gc
{
    private:
       Environment  *PrevEnv ;
       List<Binding *> *Bindings ;
    public :
       Environment( Environment *) ;
       Environment() ;
       void SetPrevEnv(Environment *) ;
       Boolean SetBinding( Variable *, DylanObject * );
       Boolean SetNewBinding( Variable *, DylanObject * );
       DylanObject *GetBinding( Variable * );
       List<Binding *> *GetBindings( ) { return Bindings ; }
       Environment *GetPrevEnv() { return PrevEnv ; }
} ;
#endif
