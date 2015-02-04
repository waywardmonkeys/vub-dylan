#ifndef _FUNCTION
#define _FUNCTION
#include "object.h"
class function : public DylanObject
{
   private:
      char *fct ;
      Method *fct_body ; 
      Environment *Env ;
      PRIM primitive ;
   public :
     function( ) ;
     function( char *s ) ;
     function( Method *B ) ;
     function( DylanObject *p ) ;

     void         Setter(char *s) ;
     void         Getter(char *s) ;
     Method      *GetBody() ;
     void         Print(int *) ;
     void         SetEnv( Environment *) ;
     Environment *GetEnv() ;
} ;
#endif
