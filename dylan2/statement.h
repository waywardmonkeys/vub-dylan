/*
 +------------------------------------------------------------------
 | FILENAME  : statement.h
 | DATE      : 01/11/1994
 |
 | ABSTRACT  : Bevat de definitie van de dylan statements.
 |             Enkel het block statement mankeert nog.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _STATEMENT
#define _STATEMENT

#include "types.h"
#include "body.h"
#include "expression.h"
#include "symbol.h"

class Statement : public Expression
{
   private :
   public :
      virtual void Print(int *) = 0 ;
      virtual DylanObject *GetValue(Environment *) = 0 ;
} ;

class If : public Statement
{
    private :
        Expression *Condition ;
        Body       *Then_clause ;
        Body       *Else_clause ;
    public :
       If( Expression *C, Body *T, Body *E )
           { Condition = C ;
             Then_clause = T ;
             Else_clause = E ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class While : public Statement
{
    private:
       Expression *Condition ;
       Body       *While_body ;
    public :
       While( Expression *C , Body *B )
          { Condition = C ; While_body = B ; } 
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Until : public Statement 
{
    private:
       Expression *Condition ;
       Body       *Until_body ;
    public :
       Until( Expression *C, Body *B )
          { Condition = C ; Until_body = B ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Unless : public Statement 
{
    private:
       Expression *Condition ;
       Body       *Unless_body ;
    public :
       Unless( Expression *C, Body *B )
          { Condition = C ; Unless_body = B ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Begin : public Statement 
{
    private:
       Body       *Begin_body ;
    public :
       Begin( Body *B )
          { Begin_body = B ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;
struct CaseBody
{   List<Expression *> *tests ;
    List<Body *> *bodies ; } ;

class Case : public Statement
{
    private :
        List<Expression *> *Tests ;
        List<Body *> *Bodies ;
    public :
        Case( List<Expression *> *T, List<Body *> *B )
            { Tests = T ; Bodies = B ; }
        void Print(int *) ;
        DylanObject *GetValue(Environment *) ;
} ;

class SelectElement     
{
    private :
        List<Expression *> *Matches ;
        Body *SelectBody ;
    public:
        SelectElement( List<Expression *> *M, Body *B )
            { Matches = M ; SelectBody = B ; }
        void Print(int *) ;
        DylanObject *GetValue(Environment *) ;
} ;

class Select : public Statement
{
    private :
        Expression *Test ;
        List<SelectElement *> *Elements ;
    public :
        Select( Expression *T, List<SelectElement *> *B )
            { Test = T ; Elements = B ; }
        void Print(int *) ;
        DylanObject *GetValue(Environment *) ;
} ;

class Clause 
{
   protected :
      Boolean Initialized ;
   public :
      virtual void Print(int *) = 0 ;
      virtual DylanObject* GetValue(Environment *) = 0 ;
} ;

class Explicit_clause : public Clause 
{
   private:
      Variable *var ;
      Expression *when ;
      Expression *then ;
   public :
      Explicit_clause( Variable *v, Expression *e1, Expression *e2 )
         { Initialized = FALSE ; var = v ; when = e1; then = e2 ; }
      void Print(int *) ;
      DylanObject *GetValue(Environment *) ;
} ;

class Bound 
{
   private:
   public :
      virtual void Print(int *) = 0 ;
      virtual Boolean CheckBound( Environment *, DylanObject *) = 0 ;
} ;

class To : public Bound
{
   private:
      Expression *Exp ;
   public :
      void Print(int *) ;
      DylanObject *GetValue(Environment *) ;
      To( Expression *E ) { Exp = E ; } 
      Boolean CheckBound( Environment *, DylanObject *) ;
} ;

class Below : public Bound
{
   private:
      Expression *Exp ;
   public :
      void Print(int *) ;
      DylanObject *GetValue(Environment *) ;
      Below( Expression *E ) { Exp = E ; } ;
      Boolean CheckBound( Environment *, DylanObject *) ;
      
} ;

class Above : public Bound
{
   private:
      Expression *Exp ;
   public :
      void Print(int *) ;
      DylanObject *GetValue(Environment *) ;
      Above( Expression *E ) { Exp = E ; }
      Boolean CheckBound( Environment *, DylanObject *) ;
} ;

class Numeric_clause : public Clause 
{
   private :
      Variable *var ;
      symbol   *incr_op ;
      Expression *start ;
      Bound      *bound ;
      Expression *incr ;
   public :
      Numeric_clause( Variable *v, Expression *E, Bound *B, Expression *I )
             { Initialized = FALSE ; 
               incr_op = new symbol( "+" ) ;
               var = v ; 
               start = E; 
               bound = B; 
               incr = I; }
      void Print(int *) ;
      DylanObject *GetValue(Environment *) ;
} ;

class Collection_clause : public Clause 
{
    private:
        Expression *collection ;
        DylanObject *collec ;
        int index ;
        Variable *var ;
    public :
        Collection_clause( Variable *v , Expression *E ) 
            { Initialized = FALSE ; index = 0; var = v ; collection = E ; }
      void Print(int *) ;
      DylanObject *GetValue(Environment *) ;
} ;

enum TypeForTest { while_test, until_test } ;

class For : public Statement
{
   private:
      List<Clause *> *Clauses ;
      Expression     *EndTest ;
      TypeForTest     TypeTest ;
      Body           *ForBody ;
      Body           *FinallyBody ;
   public :
      void Print(int * ) ;
      DylanObject *GetValue(Environment *) ;
      For(List<Clause *> *C ,
          Expression *E,
          TypeForTest t,
          Body *B ,
          Body *FB )
        { Clauses = C ; EndTest = E ; TypeTest = t ; ForBody = B ; FinallyBody = FB ; }
      For(List<Clause *> *C ,
          Body *B ,
          Body *FB )
        { Clauses = C ; EndTest = NULL ; ForBody = B ; FinallyBody = FB ; }
} ;
#endif
