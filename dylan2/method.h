/*
 +------------------------------------------------------------------
 | FILENAME  : method.h
 | DATE      : 10/11/1994
 |
 | ABSTRACT  : Definitie van methoden.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _METHOD
#define _METHOD
#include "list.h"
#include "class.h"
#include "body.h" 
#include "variable.h"
#include "object.h"
#include "types.h"
#include "function.h"

enum method_adjectives { none, open_method, sealed_method } ;
class Parameter : public Variable
{
    private :
      parameter_types Type ;
      char *name ;
      char *keyword ;
      Expression *e ;

    public :
      Parameter( parameter_types t ,
                 char *s ,
                 Expression *c ) : Variable( s,c )
        { Type = t; name = s; e = c ; keyword = NULL ; }

      Parameter( parameter_types t ,
                 char *s ,
                 Expression *c,
                 char *k ) : Variable(s,c)
        { Type = t; name = s; e = NULL ; keyword = NULL ; }
      Parameter( parameter_types t ,
                 char *s ,
                 char *c,
                 Expression *k ) : Variable(s)
        { Type = t; name = s; e = k ; keyword = c ; }
      Parameter( char *s ,
                 Expression *k ) : Variable(s)
        { Type = normal; name = s; e = k ; keyword = NULL ; }
      void Print(int *) {} ;
      parameter_types ParaType() { return Type ; } 
      char *GetKeyword() { return keyword ; } 
      Expression *GetSingleton() { return e ; }
} ;

class Method : public Expression
{
   private:
      char *Name ;
      method_adjectives   MethodAdj ;
      Body  *MethodBody ;
      List<Parameter *> *Parameters ;
      List<Variable *> *VarList ;
      PRIM prim ;

   public:
      Method( List<Parameter *> *p ,
              List<Variable *> *v ,
              Body *b )
         { Parameters = p ; VarList = v ; MethodBody = b ; }
      Method( List<Parameter *> *p ,
              Variable *v ,
              Body *b )
         { Parameters = p ; 
           VarList = new List<Variable *> ; 
           VarList->AppendItem(v) ;
           MethodBody = b ; }

      Method( List<Parameter *> *p ,
              List<Variable *> *v  )
         { Parameters = p ; VarList = v ; MethodBody = NULL ; }
      Method( List<Parameter *> *p ,
              Variable *v )
         { Parameters = p ; 
           VarList = new List<Variable *> ; 
           VarList->AppendItem(v) ;
           MethodBody = NULL ; }
      Method ( char *s ,
               List<Parameter *> *p,
               PRIM g )
             { Name = s ;
               Parameters = p ;
               MethodAdj = none ;
               VarList = NULL ;
               prim = g ; } 
      char *GetName() ;
      void SetName(char *s ) { Name = s ; } ;
      void SetMethodAdj( method_adjectives adj ) { MethodAdj = adj ; }
      void Print(int *) ;
      PRIM Primitive() { return prim ; }
      DylanObject *GetValue(Environment *) 
             { return new function(this) ; } 
      List<Parameter *> *GetParameters() { return Parameters ; }
      List<Variable *> *GetVarList() { return VarList; }
      Boolean CheckTypes( List<DylanObject *> *,
                          List<DylanObject *> *,
                          List<DylanObject *> *,
                          List<DylanObject *> * ) ;
      Body *GetBody() { return MethodBody ; }
      int operator < ( Method &M1) ;
} ;

typedef struct State
  {   Method **SArray ;
      int     *MaxSort ;
      int     *AnIndex ;
      void     Print(int *) {} ;
  } State ;

class MethodDictionnary
{
  private:
        struct MethodStruct
        {
           Method *Meth ;
           int     scope ;
           MethodStruct *next ;
           MethodStruct *prev ;
        } ;

        struct MethodDict
        {
            char    Name[255] ;
            MethodStruct *Meth ;
            MethodDict *next ;
        } ;

        struct  MethodDict *SymbolList ;
        struct  MethodDict *TopOfList ;
        List<State *> *States ;
        Method **SortArray ;
        int    *MethodsToSort ;
        int    *MethodIndex ;
   public:
      MethodDictionnary() ;     
      void InsertMethod( Method *M, int AScope ) ;
      Method *GetMethod() ;
      void  SaveState() ;
      void  RestoreState() ;

      Boolean   SearchMethod( char *Name,
                              List<DylanObject *> *,
                              List<DylanObject *> *,
                              List<DylanObject *> *,
                              List<DylanObject *> * ) ;
      void Dump() ;
} ;

extern MethodDictionnary MethodDict ;
#endif
