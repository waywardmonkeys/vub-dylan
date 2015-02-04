/*
 +------------------------------------------------------------------
 | FILENAME  : expression.h
 | DATE      : 01/11/1994
 |
 | ABSTRACT  : klasse definitie van een expressie.
 |
 | CHANGES   : V1.0 : 
 +------------------------------------------------------------------
*/
#ifndef _EXPRESSION
#define _EXPRESSION
#include <stdio.h>
#include "types.h"
#include "list.h"
#include "object.h"
#include "keyword.h"
#include "const.h"

class Method ;

class Expression : public Constituent
{
    private :

    public :
     DylanObject *FindMethod( char *op, DylanObject *Object1, DylanObject *Object2, Environment * ) ;
     virtual void Print(int * ) = 0  ;
     virtual DylanObject * GetValue(Environment *) = 0 ;
     void ReEval(Environment *) {} ;
} ;

class Assignment : public Expression
{
    private:
        Expression *leftside ;
        Expression *rightside ;
    public:
        Assignment( Expression *E1, Expression *E2 ) { leftside = E1; rightside = E2; }
        DylanObject *GetValue(Environment *) ;
        void Print(int *) ;
} ;


class AddSub : public Expression
{
    protected:
       Expression *E1 ;
       Expression *E2 ;
    public:
       virtual void Print(int *)  = 0;
       virtual DylanObject * GetValue(Environment *) = 0;
} ;

class Add : public AddSub
{
   private:
   public :
       Add( Expression *exp1, Expression *exp2 ) { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Sub : public AddSub
{
   private:
   public :
       Sub( Expression *exp1, Expression *exp2 ) { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Or : public AddSub
{
   private:
   public :
       Or( Expression *exp1, Expression *exp2 ) { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class MulDiv : public Expression
{
    protected:
       Expression *E1 ;
       Expression *E2 ;
    public:
       virtual void Print(int *) = 0 ;
       virtual DylanObject * GetValue(Environment *) = 0 ;
} ;

class Mul : public MulDiv
{
   private:
   public :
       Mul( Expression *exp1, Expression *exp2 ) { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Div : public MulDiv
{
   private:
   public :
       Div( Expression *exp1, Expression *exp2 ) { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class And : public MulDiv
{
   private:
   public :
       And( Expression *exp1, Expression *exp2 ) { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject *GetValue(Environment *) ;
} ;

class Subexp : public Expression
{
   private:
      Expression *E ;
   public :
      Subexp( Expression *exp ) { E = exp ; }
      void Print( int * ) ;
      DylanObject *GetValue(Environment *) ;
} ;

class VarRef : public Expression
{
   private:
      Variable *V  ;
   public :
      VarRef( Variable *var ) { V = var ; } 
      void Print( int * ) ;
      DylanObject *GetValue(Environment *) ;
} ;

class ConstRef : public Expression
{
   private:
      DylanObject *L ;
   public :
      ConstRef( DylanObject *cte ) { L = cte ; }
      void Print( int * ) ;
      DylanObject *GetValue(Environment *) ;
} ;

class ClassRef : public Expression
{
   private :
       Expression *LeftDot ;
       char *Name ;
   public :
      ClassRef ( Expression *E , char *s )
          { LeftDot = E ; Name = s ; }
      void Print(int *) ;
      DylanObject * GetValue(Environment *) ;

} ;

class Argument
{
  private :
     Expression *E ;
     char       *Keyword ;
  public :
     Argument( Expression *Exp ) { E =Exp ; Keyword = NULL ; }
     Argument( Expression *Exp, char *s ) { E =Exp ; Keyword = s ; }
     void Print(int *) ;
     DylanObject * GetValue(Environment *) ;
     Expression *GetExpression() { return E ; }
     int IsKeyword() { return ( Keyword != NULL ) ; }
} ;

class MethodRef : public Expression
{
   private :
       Expression *operand ;
       List<Argument *> *Arguments;
   public :
      MethodRef ( Expression *E , List<Argument *> *L )
          { operand = E ; Arguments = L ; }
      void Print(int *) ;
      DylanObject * GetValue(Environment *) ;

} ;

class VectorRef : public Expression
{
   private :
       Expression *operand ;
       List<Argument *> *Arguments;
   public :
      VectorRef ( Expression *E , List<Argument *> *L )
          { operand = E ; Arguments = L ; }
      void Print(int *) ;
      DylanObject * GetValue(Environment *) ;

} ;

class Not : public Expression
{
   private :  
       Expression *operand ;
   public :
       Not (Expression *E ) { operand = E ; } 
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;
} ;

class Minus : public Expression
{
   private :  
       Expression *operand ;
   public :
       Minus (Expression *E ) { operand = E ; } 
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;

class Conditional : public Expression
{
    protected:
       Expression *E1 ;
       Expression *E2 ;
    public:
       virtual void Print(int *) = 0 ;
       virtual DylanObject *GetValue(Environment *) = 0 ;
} ;

class Eq : public Conditional
{
   private :  
   public :
       Eq (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
class Ne : public Conditional
{
   private :  
   public :
       Ne (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
class Lt : public Conditional
{
   private :  
   public :
       Lt (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
class Gt : public Conditional
{
   private :  
   public :
       Gt (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
class Le : public Conditional
{
   private :  
   public :
       Le (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
class Ge : public Conditional
{
   private :  
   public :
       Ge (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
class Identity : public Conditional
{
   private :  
   public :
       Identity (Expression *exp1, Expression *exp2 )
            { E1 = exp1 ; E2 = exp2 ; }
       void Print(int *) ;
       DylanObject * GetValue(Environment *) ;

} ;
extern Expression *MakeExpression ( char *op, Expression *E1, Expression *E2 ) ;
extern ClassDictionnary ClassDict ;
#endif
