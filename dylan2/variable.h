/*
 +------------------------------------------------------------------
 | FILENAME  : variable.h
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Definitie van een variable + variabele dictionnary.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _VARIABLE
#define _VARIABLE
#include "const.h"
#include "list.h"
#include "expression.h"
#include "class.h"
#include "environment.h"

struct tempvar
   { const char *name;
     Expression *type ; } ;

class Variable : public Constituent
{
    private :
        const char *Name ;
        int index ;
        Expression  *ClassVar ;
        Expression *Init ;
        Boolean  ReadOnly ;
        DylanObject *Value ;
        Boolean Initialized ;
    public :
        Variable(const char *a, int c, Expression *d, Expression *e, Boolean f) ;
        Variable(const char *a ) ;
        Variable(const char *a, Expression *d) ;
        Variable( const char *a, Boolean b ) ;
        const char *GetName() ;
        Expression *GetType() ;
        Boolean IsConstant() ;
        void  SetVar( Expression *exp ) ; 
        void  SetValue( Environment *Env, DylanObject *o  ) ; 
        void Print(int *) ; 
        DylanObject *GetValue(Environment * ) ;
        void SetIndex( int x ) { index = x ; }
        void SetConstant(){  ReadOnly = TRUE ; }
        void ReEval(Environment *Env ) 
                { 
                   Initialized = FALSE ;
                   // Value = Init->GetValue(Env) ;
                   // Env->SetNewBinding( this, Value ) ;
                }
        void Dump() { if ( Value != NULL ) Value->Print(0) ; }
} ;


class DataDictionnary
{
   private:
        struct DataStruct
          {
            Variable *Var ;
            int Scope ;
            DataStruct *next ;
            DataStruct *prev ;
          } ;
        struct DataStruct *SymbolList ;
        struct DataStruct *TopOfList ;
        struct DataStruct *EndOfList ;

   public:
      DataDictionnary() ;     
      void InsertVar( Variable *Var, int VarScope ) ;
      Variable *GetVar() ;
      Boolean   SearchVar( Variable *Var, int VarScope ) ;
      void Dump() ;
} ;
#endif
