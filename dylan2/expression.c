/*
 +------------------------------------------------------------------
 | FILENAME  : expression.c
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Evalueren van expressies + pretty print
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include "expression.h"
#include "variable.h"
#include "class.h"
#include "method.h"
#include "list_type.h"
#include "boolean.h"
#include "apply.h"
#include <string.h>

static Variable *PtrVar = NULL ;
static Slot_specs *ClassSlot = NULL  ;
static int CollectionElement = -1 ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : Expression::FindMethod
 | INPUT     : const char *  : een operand
 |             DylanObject * : een object
 |             DylanObject * : een object
 | OUTPUT    : -
 | RETURN    : object <op> <object
 | DATE      :
 |
 | ABSTRACT  : Deze functie gaat, voor de elementaire operanden
 |             (+,-,*,/,..), opzoek in de methoddictionnary naar
 |             de correcte uitvoeringen. 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Expression::FindMethod( const char *op, DylanObject *Object1, DylanObject *Object2, Environment *Env )
{
   List<DylanObject *> *P ;
   List<Parameter *> *ParList ;
   Method *FuncMethod ;
   Body   *FuncBody ;
   DylanObject *X ;

   P = new List<DylanObject *> ;
   P->AppendItem(Object1) ;
   P->AppendItem(Object2) ;
   // deze NULL'en moeten nog weg !
   if ( MethodDict.SearchMethod( op, P, NULL, NULL, NULL )) 
   {
     FuncMethod = MethodDict.GetMethod() ;
     ParList = FuncMethod->GetParameters() ;
     if ( FuncMethod->Primitive() != NULL )
     {
        return (FuncMethod->Primitive())(Object1, Object2) ;
     }
     ParList->MoveTo(1) ;
     Env->SetNewBinding(ParList->GetItem(), Object1 ) ;
     ParList->MoveTo(2) ;
     Env->SetNewBinding(ParList->GetItem(), Object2 ) ;
     FuncBody = new Body(FuncMethod->GetBody() ) ;
     X = FuncBody->GetValue(Env) ;
     ClassSlot = NULL ;
     return X ;
   }
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Assignment::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een assignment
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Assignment::Print(int *indent)
{
   leftside->Print(indent) ;
   printf( " := " ) ;
   rightside->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Assignment::GetValue()
 | INPUT     : Environment
 | OUTPUT    : -
 | RETURN    : false_object
 | DATE      : 01/12/1994
 |
 | ABSTRACT  : Toewijzen van een waarde aan een variable.
 |             Er wordt aan type checking gedaan wanneer het type van 
 |             de variable niet <object> is.
 |             Er wordt ook een onderscheid tussen het feit of
 |             het een variable is of een slot van een klasse.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Assignment::GetValue(Environment *Env)
{
   Variable     *var ;
   Slot_specs   *slot ;
   int           index ;
   DylanObject  *Value ;
   Boolean       Ok ;
   int           i ;
   int           NbrClasses ;
   DylanObject **PrecedenceList ;

   CollectionElement = -1 ;
   /* wanneer na evaluatie blijkt dat de waarde nog altijd een
      symbool is dan betekent dit dat geen variable is */
   ClassSlot = NULL ;
   PtrVar    = NULL ;

   if ( strcmp( leftside->GetValue(Env)->GetName(), "<symbol>") == 0)
      error( "This is not a variable !" ) ; ;
   
   if ( ClassSlot == NULL )
   {
      var = PtrVar ;
      if ( CollectionElement > -1 )
      {
         index = CollectionElement ;

         // in een collection kunnen we gelijk wat stoppen.
         Value = rightside->GetValue(Env) ;
         var->GetValue(Env)->Setter( index, Value ) ;
      }
      else
      {
         Ok = FALSE ;
         Value = rightside->GetValue(Env) ;

         if ( strcmp(var->GetType()->GetValue(Env)->GetName(), "<object>" ) == 0 )
         {
            Ok = TRUE ;
         }
         else
         {
            if ( strcmp(var->GetType()->GetValue(Env)->GetName(), Value->GetName() ) == 0 )
                   Ok = TRUE ;
            PrecedenceList = Value->GetSuperclass(&NbrClasses) ; 

            for( i = NbrClasses - 1 ; i >= 0; i-- )
            {
               if ( strcmp(PrecedenceList[i]->GetName(), var->GetType()->GetValue(Env)->GetName()) == 0 ) Ok = TRUE ;

            }
           
         }
         if ( Ok ) var->SetValue(Env, Value) ;
         if ( ! Ok ) error( "Type mismatch !") ;
      } 
   }
   else
   {  
      slot = ClassSlot ;
      if ( slot->GetSlotAllocation() != constant_class )
      {
         if ( CollectionElement > -1 )
         {
            index = CollectionElement ;
   
           Value = rightside->GetValue(Env) ;
           slot->GetValue()->Setter( index, Value ) ;
         }
         else
         {
            Ok = FALSE ;

            Value = rightside->GetValue(Env) ;
            if ( strcmp(slot->GetType()->GetName(), "<object>" ) == 0 )
            {
               Ok = TRUE ;
            }
            else
            {
               if ( strcmp(slot->GetType()->GetName(), Value->GetName() ) == 0 )
                      Ok = TRUE ;
               PrecedenceList = slot->GetType()->GetSuperclass(&NbrClasses) ; 
   
               for( i = 0 ; i < NbrClasses; i++ )
               {
                  if ( strcmp(PrecedenceList[i]->GetName(), Value->GetName()) == 0 ) Ok = TRUE ;
   
               }
              
            }
            if ( Ok ) slot->SetValue( Value) ;
           }    
      }
      else
      { 
         error( "trying to assign a value to a constant slot" ) ;
      }
   }
   PtrVar    = NULL ;
   ClassSlot = NULL ;
   // return var->GetValue(Env) ;
   return false_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Eq::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer equal
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Eq::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " = " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Lt::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer kleiner dan
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Lt::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " < " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Gt::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer groter dan
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Gt::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " > " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Le::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer kleiner dan of gelijk 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Le::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " <= ") ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : ge::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer groter dan of gelijk
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Ge::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " >= " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Ne::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer niet gelijk aan 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Ne::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " ~= " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Identity::Print
 | INPUT     : int = indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer equal
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Identity::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " == " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Eq::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op gelijkheid van 2 objecten ( hun respectievelijke
 |             waarde.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject  *Eq::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "=", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Ne::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op != van 2 objecten ( hun respectievelijke
 |             waarde.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject  *Ne::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "~=", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Lt::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op < van 2 objecten ( hun respectievelijke
 |             waarde.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject  *Lt::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "<", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Gt::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op > van 2 objecten ( hun respectievelijke
 |             waarde.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject  *Gt::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( ">", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Le::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op <= van 2 objecten ( hun respectievelijke
 |             waarde.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject  *Le::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "<=", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Ge::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op >= van 2 objecten ( hun respectievelijke
 |             waarde.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject  *Ge::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( ">=", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Identity::GetValue
 | INPUT     : Environment : omgeving in de welke we de code moeten uitvoeren
 | OUTPUT    : -
 | RETURN    : Booleanobject
 | DATE      :
 |
 | ABSTRACT  : Testen op == van 2 objecten ( hun respectievelijke
 |             pointers.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject  *Identity::GetValue(Environment *Env)
{
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Add::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer '+' expressie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Add::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " + " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Sub::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer voor '-' expressies
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Sub::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " - " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Or::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer voor 'or' expressies
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Or::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " | " ) ;
   E2->Print(indent) ;
} 


/*
 +------------------------------------------------------------------
 | FUNCTION  : Add::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : Een dylan object
 | DATE      :
 |
 | ABSTRACT  : Som van 2 objecten
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Add::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "+", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Sub::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Verschil van 2 objecten
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Sub::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "-", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Or::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : De or van 2 objecten , gewoonlijk zou dit
 |             een boolean object moeten teruggeven, maar niks is zeker.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Or::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "|", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Mul::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print van een '*' expressie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Mul::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " * " ) ;
   E2->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Div::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print van een '/' expressie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Div::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " / " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : And::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print van een 'and' expressie.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void And::Print(int *indent)
{
   E1->Print(indent) ;
   printf( " & " ) ;
   E2->Print(indent) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Mul::GetValue
 | INPUT     : Environment : omgeving waarin de expressie wordt 
 |                           geevalueerd.
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Vermenigvuldiging van 2 objecten.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Mul::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "*", O1,O2, Env ) ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : Div::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Deling van 2 objecten
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Div::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "/", O1,O2, Env ) ;

}
/*
 +------------------------------------------------------------------
 | FUNCTION  : And::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object 
 | DATE      :
 |
 | ABSTRACT  : de logische and van 2 objecten 
 |             |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *And::GetValue(Environment *Env)
{
   DylanObject *O1 ;
   DylanObject *O2 ;

   O1 = E1->GetValue(Env) ;
   O2 = E2->GetValue(Env) ;

   return FindMethod( "&", O1,O2, Env ) ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Not::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print van een '~' expressie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Not::Print(int *indent) 
{
   printf( " ~ " ) ;
   operand->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Not::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : Boolean object
 | DATE      :
 |
 | ABSTRACT  : ~ van een expressie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Not::GetValue(Environment *Env)
{
   Boolean boolean ;

   operand->GetValue(Env)->Getter(&boolean) ;
   return ( new boolean_type( ! boolean ) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Minus::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print van een minus expressie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Minus::Print(int *indent) 
{
   printf( " - " ) ;
   operand->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Minus::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : NULL
 | DATE      :
 |
 | ABSTRACT  : Deze dummy functie wordt opgelost in de Sub, omdat
 |             een minus expressie ( -a ) gelijk is aan 0 - a  
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject * Minus::GetValue(Environment *Env)
{
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : VarRef::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een variable referentie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void VarRef::Print(int *indent) 
{
   printf( "%s", V->GetName()) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ConstRef::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een constante referentie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void ConstRef::Print(int *indent) 
{
   L->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Subexp::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een sub expressie.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Subexp::Print(int *indent) 
{
   printf( "( ") ;
   E->Print(indent) ;
   printf(" )") ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : VarRef::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : Waarde van de variable
 | DATE      :
 |
 | ABSTRACT  : Teruggeven van de waarde van een variable binnen een
 |             bepaalde context.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *VarRef::GetValue(Environment *Env)
{
  PtrVar = V ;
  return V->GetValue(Env)  ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ConstRef::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : Een constante
 | DATE      :
 |
 | ABSTRACT  : Opgelet, de environment variable wordt niet
 |             gebruikt, omdat een constante een constante is
 |             en dit in gelijk welke context.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *ConstRef::GetValue(Environment *Env)
{
  return L ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Subexp::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van de sub expressie binnen een bepaalde 
 |             context.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Subexp::GetValue(Environment *Env)
{
  return E->GetValue(Env) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassRef::Print
 | INPUT     : int : een indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een class referentie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void ClassRef::Print(int *indent )
{
    LeftDot->Print(indent) ;
    printf( ".%s", Name );
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : ClassRef::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylanobject
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van het slot van een klasse.
 |             Let wel de linkerkant  en de rechterkant kunnen beiden
 |             een expressie zijn.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *ClassRef::GetValue(Environment *Env )
{
   DylanObject *AVar ;

   AVar = LeftDot->GetValue(Env) ;
   ClassSlot = AVar->ReturnSlot( Name ) ;

   return ClassSlot->GetValue()  ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Argument::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een argument van een methode.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Argument::Print(int *indent )
{
    if ( Keyword != NULL ) printf( "%s ", Keyword ) ;
    E->Print(indent) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Argument::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van een argument ( let op een argument kan
 |             een keyword zijn ). De argumenten worden geevalueerd in
 |             de omgeving van de caller.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Argument::GetValue(Environment *Env )
{
   static keyword *keywordarg ;

   if ( Keyword != NULL )
   {
      keywordarg = new keyword( Keyword, E->GetValue(Env) ) ;
      return keywordarg ;
   }
   return E->GetValue(Env) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodRef::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een methode oproep
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void MethodRef::Print(int *indent )
{
    int i ;

    operand->Print(indent) ;
    printf( "(" );
    for( i = 1; Arguments != NULL && i <= Arguments->GetSize(); i++ )
    {
       Arguments->MoveTo(i) ;
       Arguments->GetItem()->Print(indent) ;
       if ( i != Arguments->GetSize() ) printf( ", ");
    }
    printf( ")") ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodRef::GetValue
 | INPUT     : Environment
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van een method call
 |             1- evaluatie van de argumenten 
 |             2- evaluatie van de operand
 |             3- apply operand to arguments
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *MethodRef::GetValue( Environment *Env)
{
   int i ;

   List<DylanObject *> *P ;
   List<DylanObject *> *Rest = NULL ;
   List<DylanObject *> *Next = NULL ;
   List<DylanObject *> *Keys = NULL ;
   DylanObject *ArgumentValue ;

   DylanObject *Arg[10] ;
   DylanObject *X ;

   P = new List<DylanObject *> ;
   Rest = new List<DylanObject *> ;
   Next = new List<DylanObject *> ;
   Keys = new List<DylanObject *> ;


   for( i = 1; Arguments != NULL && i <= Arguments->GetSize(); i++ )
   {
     Arguments->MoveTo(i) ;
     ArgumentValue = Arguments->GetItem()->GetValue(Env) ;
     if ( ArgumentValue == NULL )
     {
        error( "Uninitialized argument supplied !" ) ;
     }
     P->AppendItem(ArgumentValue) ;
     Arg[i] = ArgumentValue ;
   }

   X = apply ( operand->GetValue(Env), Env, P, Arg, Arguments ) ;
   ClassSlot = NULL ;
   return X ;

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : VectorRef::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty print van een vector referentie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void VectorRef::Print(int *indent )
{
    int i ;

    operand->Print(indent) ;
    printf( "[" );
    for( i = 1; i <= Arguments->GetSize(); i++ )
    {
       Arguments->MoveTo(i) ;
       Arguments->GetItem()->Print(indent) ;
       if ( i != Arguments->GetSize() ) printf( ", ");
    }
    printf( "]") ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Vectorref::GetValue
 | INPUT     : Environment
 | OUTPUT    : -
 | RETURN    : een dylan object
 | DATE      :
 |
 | ABSTRACT  : Evaluatie van een array reference
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *VectorRef::GetValue(Environment *Env )
{
   long index ;
   long indexj ;
   long multiplier ;
   int  j ;
   static DylanObject  *Elements ;
   List<DylanObject *> *Dims ;

   Arguments->MoveTo(1) ;
   Arguments->GetItem()->GetValue(Env)->Getter(&index) ;
   // Elements = new List<DylanObject *> ;
   Dims = operand->GetValue(Env)->GetDimensions() ;
   if ( Dims != NULL )
   {
       index = 0 ;
       multiplier = 1 ;
       for( j = Arguments->GetSize(); j >= 1; j-- )
       {
          Arguments->MoveTo(j) ;
          if ( j != Arguments->GetSize() )
          {
             Dims->MoveTo(j + 1 ) ;
             Dims->GetItem()->Getter(&indexj) ;
             multiplier = multiplier * indexj ;
          }
          Arguments->GetItem()->GetValue(Env)->Getter(&indexj) ;
          index  = index + multiplier * indexj ;
       }
   }
   Elements = operand->GetValue(Env)->GetElement(index) ;
   /*if ( index + 1 > Elements.GetSize() )
   {
      printf( "index = %d, size = %d ", index, Elements.GetSize() ) ;
      error( "index out of range !" ) ;
   }
   Elements.MoveTo( index + 1 ) ;
   */
   CollectionElement = index ;
   // return Elements.GetItem() ;
   return Elements ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MakeExpression
 | INPUT     : een operand
 |             een expressie
 |             een expressie
 | OUTPUT    : -
 | RETURN    : een nieuwe expressie
 | DATE      :
 |
 | ABSTRACT  : obsolete code, moet vervangen worden in de yacc file
 |             door hun respectievelijke constructors.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Expression *MakeExpression ( const char *op, Expression *E1, Expression *E2 )
{
  if ( strcmp (op,  "*" ) == 0)
     return (new Mul( E1, E2)) ;

  if ( strcmp (op,  "&" ) == 0)
     return ( new And ( E1, E2)) ;

  if ( strcmp (op,  "/" ) == 0)
     return (new Div( E1, E2)) ;

 if ( strcmp(op, "+") == 0 )
      return (new Add(  E1,E2 )) ;

 if ( strcmp(op, "|") == 0 )
      return (new Or( E1,E2 )) ;

 if ( strcmp(op, "-") == 0 )
      return (new Sub( E1,E2 )) ;

 if ( strcmp(op,"=") == 0 )
      return  (new Eq( E1,E2 )) ;

 if ( strcmp(op,"==") == 0 )
      return  (new Identity( E1,E2 )) ;

 if ( strcmp(op,"~=") == 0 )
      return  (new Ne( E1,E2 )) ;

 if ( strcmp(op,"<") == 0 )
      return (new Lt (E1,E2 )) ;

 if ( strcmp(op,">") == 0 )
      return (new Gt( E1,E2 )) ;

 if ( strcmp(op,"<=") == 0 )
      return (new Le(E1,E2 )) ;

 if ( strcmp(op,">=") == 0 )
      return  (new Ge(E1,E2 )) ;

 if ( strcmp(op,":=") == 0 )
      return  (new Assignment(E1,E2 )) ;
 return NULL ;
}
