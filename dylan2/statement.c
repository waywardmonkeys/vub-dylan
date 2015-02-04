/*
 +------------------------------------------------------------------
 | FILENAME  : statement.c
 | DATE      : 10/11/1994
 |
 | ABSTRACT  : implementatie van een aantal dylan statements
 |             De volgende statements zijn geimplementeerd :
 |             IF ... THEN ... ELSE ...
 |             WHILE .... END WHILE
 |             UNTIL ..... END UNTIL
 |             UNLESS .... END UNLESS
 |             FOR .... END FOR
 |             BEGIN ..... END BEGIN
 |             De SELECT en het BLOCK statement moeten 
 |             nog verder uitgewerkt worden.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include "statement.h"
#include "environment.h"
#include "boolean.h"
#include "variable.h"
#include "apply.h"
#include "integer.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : If::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een if statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void If::Print(int *indent )
{
   printf( "if (" ) ;
   Condition->Print(indent) ;
   printf( " )\n " ) ;
   *indent += 5 ;
   Then_clause->Print(indent) ;
   if ( Else_clause != NULL ) 
   {
      printf( "\nelse\n" ) ;
      Else_clause->Print(indent) ;
   }
   *indent -= 5 ;
   printf( "\nendif ;\n" ); 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : While::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een While statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void While::Print(int *indent )
{
   printf( "while (" ) ;
   Condition->Print(indent) ;
   printf( " )\n " ) ;
   *indent += 5 ;
   While_body->Print(indent) ;
   *indent -= 5 ;
   printf( "\nend while ;\n" ); 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Until::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een until statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Until::Print(int *indent )
{
   printf( "until (" ) ;
   Condition->Print(indent) ;
   printf( " )\n " ) ;
   *indent += 5 ;
   Until_body->Print(indent) ;
   *indent -= 5 ;
   printf( "\nend until ;\n" ); 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Unless::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een unless statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Unless::Print(int *indent )
{
   printf( "unless (" ) ;
   Condition->Print(indent) ;
   printf( " )\n " ) ;
   *indent += 5 ;
   Unless_body->Print(indent) ;
   *indent -= 5 ;
   printf( "\nend unless ;\n" ); 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Begin::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Begin statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Begin::Print(int *indent )
{
   printf( "begin\n" ) ;
   *indent += 5 ;
   Begin_body->Print(indent) ;
   *indent -= 5 ;
   printf( "end begin\n " ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Case::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Case statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Case::Print(int *indent )
{
   int i ;

   printf( "case\n") ;

   for( i = 1; i <= Tests->GetSize(); i++ )
   {
      Tests->MoveTo(i) ;
      Bodies->MoveTo(i) ;
      if ( Tests->GetItem() != NULL )
      {
        Tests->GetItem()->Print(indent) ;
      }
      else
      {
        printf( " otherwise" ) ;
      }
      printf( " => " ) ;
      *indent += 5 ;
      Bodies->GetItem()->Print(indent) ;
      *indent -= 5 ;
      printf( ";\n" ) ;
   }
   printf( "end case\n" ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : SelectElement::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een SelectElement statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void SelectElement::Print(int *indent )
{
  int i ;
  if ( Matches != NULL )
  {
    for( i = 1; i<= Matches->GetSize(); i++ )
    {
       Matches->MoveTo(i) ;
       if ( i != Matches->GetSize() ) printf( ", ") ;
    }
  }
  else
  {
     printf( "otherwise " ) ;
  }
  printf( "=> ") ;
  *indent += 5 ;
  SelectBody->Print(indent) ;
  *indent -= 5 ;
  printf( "\n") ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Select::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Select statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Select::Print(int *indent )
{
   int i ;

   printf( "select ( " ) ;
   Test->Print(indent) ;
   printf( " ) \n" ) ;
   for( i = 1; i<= Elements->GetSize(); i++ )
   {
      Elements->MoveTo(i) ;
      Elements->GetItem()->Print(indent) ;
      printf( ";\n ") ;
   }
   printf( "end select\n" ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Explicit_clause::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Explicit_clause statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Explicit_clause::Print(int *indent )
{
   printf( "%s = ", var->GetName() ) ;
   when->Print(indent) ;
   printf( " then " ) ;
   then->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : To::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een To statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void To::Print(int *indent )
{
   printf (" to " ) ;
   Exp->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Above::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Above statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Above::Print(int *indent )
{
   printf (" above " ) ;
   Exp->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Below::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Below statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Below::Print(int *indent )
{
   printf (" below " ) ;
   Exp->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Numeric_clause::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Numeric_clause statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Numeric_clause::Print(int *indent )
{
   printf( "%s = from ", var->GetName() ) ;
   start->Print(indent) ;
   if ( bound != NULL ) bound->Print(indent) ;
   if ( incr != NULL )
   {
      printf( " by " ) ;
      incr->Print(indent) ;
   }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Collection_clause::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een Collection_clause statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void Collection_clause::Print(int *indent )
{
   printf( "%s in ", var->GetName() ) ;
   collection->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : For::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een For statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
void For::Print(int *indent )
{
   int i ;

   *indent += 5 ;

   printf( "for ( " ) ;
   for( i = 1; i <= Clauses->GetSize(); i++ )
   {
      Clauses->MoveTo(i) ;
      Clauses->GetItem()->Print(indent) ;
      if ( i != Clauses->GetSize() ) printf( ",\n") ;
   }
   printf( ") \n" ) ;
   if ( EndTest != NULL )
   {
      if ( TypeTest == until_test ) printf( "until " ) ;
      if ( TypeTest == while_test ) printf( "while " ) ;
      EndTest->Print(indent) ;
      printf( "\n" ) ;
   }
   ForBody->Print(indent) ;
   if ( FinallyBody != NULL )
   {
     printf( "finally\n") ;
     *indent += 5 ;
     FinallyBody->Print(indent) ;
     *indent -= 5 ;
   }
   *indent -= 5 ;
   printf( "\nend for ;\n" ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : if::GetValue
 | INPUT     : Environment * : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een if statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *If::GetValue( Environment *Env )
{
    Boolean bool ;
    DylanObject *Cond ;
    Body *Local ;
    Environment *NewEnv ;

    NewEnv = new Environment( Env ) ;

    Cond = Condition->GetValue(Env) ; // evaluatie van de conditie
    Cond->Getter(&bool) ;

    if(bool) 
    {
       // then clause evalueren

       Local = new Body( Then_clause ) ;
       return Local->GetValue(NewEnv) ;
    }
    else if ( Else_clause != NULL )
    {
       // else clause evalueren
       Local = new Body( Else_clause ) ;
       return Local->GetValue(NewEnv) ;
    }

    return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : While::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylanobject
 | DATE      :
 |
 | ABSTRACT  : Evaluator van het while statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * While::GetValue( Environment *Env )
{
    Boolean bool ;
    static DylanObject  *Result ;
    DylanObject *Cond ;
    Environment *NewEnv ;

    NewEnv = new Environment(Env) ;
    Cond = Condition->GetValue(Env) ;
    Cond->Getter(&bool) ;
    Result = NULL ;

    while(bool) 
    {
       Result = While_body->GetValue(NewEnv) ;
       Cond = Condition->GetValue(Env) ;
       Cond->Getter(&bool) ;
    }
    return Result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Until::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een dylan object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Until::GetValue( Environment *Env )
{
    Boolean bool ;
    static DylanObject  *Result ;
    DylanObject *Cond ;
    Environment *NewEnv ;

    NewEnv = new Environment(Env) ;
    Cond = Condition->GetValue(Env) ;
    Cond->Getter(&bool) ;

    while(! bool) 
    {
       Result = Until_body->GetValue(NewEnv) ;
       Cond = Condition->GetValue(Env) ;
       Cond->Getter(&bool) ;
    }
    return Result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Unless::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een unless statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Unless::GetValue( Environment *Env )
{
    Boolean bool ;
    static DylanObject  *Result ;
    DylanObject *Cond ;
    Environment *NewEnv ;

    NewEnv = new Environment(Env) ;

    Cond = Condition->GetValue(Env) ;
    Cond->Getter(&bool) ;


    Result = NULL ;

    if(! bool) 
    {
       Result = Unless_body->GetValue(NewEnv) ;
    }

    return Result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Begin::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een begin statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Begin::GetValue( Environment *Env )
{
   Environment *NewEnv ;
   NewEnv = new Environment(Env) ;
   return Begin_body->GetValue(NewEnv) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Case::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een case statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Case::GetValue( Environment *Env )
{
   int i ;
   DylanObject *Result ;
   Environment *NewEnv ;
   Boolean bool;

   NewEnv = new Environment(Env) ;

   for( i = 1; i <= Tests->GetSize(); i++ )
   {
      Tests->MoveTo(i) ;

      // evaluatie van een test

      if ( Tests->GetItem() != NULL )
      {
         Result = Tests->GetItem()->GetValue(Env) ;
         Result->Getter(&bool) ;
      }
      else
      {
         // indien geen test = otherwise
         bool = TRUE ;
      }

      if ( bool )
      {
         Bodies->MoveTo(i) ;
         return Bodies->GetItem()->GetValue(NewEnv) ;
      }
   }
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : SelectElement::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een select element
 |             Niet geimplementeerd !
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * SelectElement::GetValue( Environment *Env )
{
return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Select::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een select
 |             Niet geimplementeerd
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Select::GetValue( Environment *Env )
{
return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Explicit_clause::GetValue
 | INPUT     : Environment :  een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluator van een explicit clause, een explicit
 |             clause is iets dat er als volgt uitziet :
 |             WHEN <condition> THEN <clause>
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Explicit_clause::GetValue( Environment *Env )
{
   if ( ! Initialized )
   {
       var->SetValue( Env, when->GetValue(Env) ) ;
       Initialized = TRUE ;
   }
   else
   {
       var->SetValue( Env, then->GetValue(Env) ) ;
   }
   return false_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : To::GetValue
 | INPUT     : Environment  : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van een to predicate, in de numerieke
 |             clausule van een for statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * To::GetValue( Environment *Env )
{
    return Exp->GetValue(Env) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : To::CheckBound
 | INPUT     : Environment : een omgeving
 |             DylanObject : de waarde van de grens
 | OUTPUT    : -
 | RETURN    : TRUE : bound overschreden
 | DATE      :
 |
 | ABSTRACT  : Test functie die ziet of de grens al of niet
 |             overschreden is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean To::CheckBound( Environment *Env, DylanObject *Obj )
{
   symbol *op ;
   DylanObject *Arg[10] ;
   List<DylanObject *> *P ;
   Boolean bool ;

   op = new symbol(">") ;
   P = new List<DylanObject *> ;

   Arg[1] = Obj ;
   P->AppendItem(Arg[1]) ;
   Arg[2] = this->GetValue(Env) ;
   P->AppendItem(Arg[2]) ;
   apply( op, Env, P, Arg, NULL )->Getter(&bool) ;
   return bool ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Above::CheckBound
 | INPUT     : Environment : een omgeving
 |             DylanObject : de waarde van de grens
 | OUTPUT    : -
 | RETURN    : TRUE : bound overschreden
 | DATE      :
 |
 | ABSTRACT  : Test functie die ziet of de grens al of niet
 |             overschreden is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean Above::CheckBound( Environment *Env, DylanObject *Obj )
{
   symbol *op ;
   DylanObject *Arg[10] ;
   List<DylanObject *> *P ;
   Boolean bool ;

   op = new symbol("<=") ;
   P = new List<DylanObject *> ;

   Arg[1] = Obj ;
   P->AppendItem(Arg[1]) ;
   Arg[2] = this->GetValue(Env) ;
   P->AppendItem(Arg[2]) ;
   apply( op, Env, P, Arg, NULL )->Getter(&bool) ;
 }

/*
 +------------------------------------------------------------------
 | FUNCTION  : Below::CheckBound
 | INPUT     : Environment : een omgeving
 |             DylanObject : de waarde van de grens
 | OUTPUT    : -
 | RETURN    : TRUE : bound overschreden
 | DATE      :
 |
 | ABSTRACT  : Test functie die ziet of de grens al of niet
 |             overschreden is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean Below::CheckBound( Environment *Env, DylanObject *Obj )
{
   symbol *op ;
   DylanObject *Arg[10] ;
   List<DylanObject *> *P ;
   Boolean bool ;

   op = new symbol(">=") ;
   P = new List<DylanObject *> ;

   Arg[1] = Obj ;
   P->AppendItem(Arg[1]) ;
   Arg[2] = this->GetValue(Env) ;
   P->AppendItem(Arg[2]) ;
   apply( op, Env, P, Arg, NULL )->Getter(&bool) ;
 }

/*
 +------------------------------------------------------------------
 | FUNCTION  : Above::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylanobject
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van het above predikaat
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Above::GetValue( Environment *Env )
{
    return Exp->GetValue(Env) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Below::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van de below predicaat (merk op dat steeds
 |             opnieuw de expressie wordt geevalueerd omdat in de 
 |             for-lus elementen van de expressie kunnen gewijzigd
 |             worden)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Below::GetValue( Environment *Env )
{
    return Exp->GetValue(Env) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Numeric_clause::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van allerlei numerieke clausules
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Numeric_clause::GetValue( Environment *Env )
{
    DylanObject *Arg[10] ;
    List<DylanObject *> *P ;

    if ( ! Initialized )
    {
       Initialized = TRUE ;
       var->GetValue(Env) ; // initialisatie incr. variable
       return false_object ;
    }
    else
    {
       P = new List<DylanObject *> ;
       Arg[1] = var->GetValue(Env) ;
       P->AppendItem(Arg[1] ) ;
       if ( incr != NULL )
       {
          Arg[2] = incr->GetValue(Env) ;
       }
       else
       {
          Arg[2] = new integer(1) ;
       }
       P->AppendItem(Arg[2] ) ;
       var->SetValue(Env, apply( incr_op, Env, P, Arg, NULL )) ;
       if ( bound != NULL )
       {
          if ( bound->CheckBound( Env, var->GetValue(Env) ) )
          {
             Initialized = FALSE ;
             var->ReEval(NULL) ;
             return true_object ;
          }
          else
          {
             return false_object ;
          }
       }
       return false_object ;
    }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Collection_clause::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van een collection clause, in feite
 |             binden we een variable aan een bepaald element van 
 |             een collectie
 |             Vb : (Evaluatie van X IN #(1,2,3,4) )
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Collection_clause::GetValue( Environment *Env )
{
   if ( ! Initialized )
   {
      collec = collection->GetValue(Env) ;
      var->SetValue(Env, collec->GetElement(index) ) ;
      index++ ;
      Initialized = TRUE ;
   }
   else
   {
      if ( index >= collec->Size() ) return true_object ;
      var->SetValue(Env, collec->GetElement(index) ) ;
      index++ ;
   }
   return false_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : For::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluator voor een for statement
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * For::GetValue( Environment *Env )
{
   int i ;
   Boolean bool ;
   Boolean b ;
   Environment *NewEnv ;

   NewEnv = new Environment(Env) ;

   bool = TRUE ;

   while( bool ) 
   {
     for( i = 1; i <= Clauses->GetSize(); i++ )
     {
        Clauses->MoveTo(i) ;
        Clauses->GetItem()->GetValue(NewEnv)->Getter(&b) ;
        if (b) bool = FALSE ;
     }

     if ( EndTest != NULL )
     {
         EndTest->GetValue(NewEnv)->Getter(&b) ;
         if ( b && TypeTest == until_test ) bool = FALSE ;
         if ( ! b && TypeTest == while_test ) bool = FALSE ;

     }
     if ( bool )
     {
        if ( ForBody != NULL ) ForBody->GetValue(NewEnv) ;
     }
   }

   if ( FinallyBody != NULL )
   {
       return FinallyBody->GetValue(NewEnv) ;
   }
   return false_object ;

}
