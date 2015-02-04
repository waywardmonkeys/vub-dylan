/*
 +------------------------------------------------------------------
 | FILENAME  : variable.c
 | DATE      : 01/09/94
 |
 | ABSTRACT  : Support voor variabelen in Dylan
 |
 | CHANGES   : 20/12/94 : toevoegen van environments
 +------------------------------------------------------------------
*/
#include "types.h"
#include "variable.h"
#include "rest_list.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::Variable
 | INPUT     : char       : naam van de variable
 |             int        : index binnen de variable
 |             Expression : type van de variable
 |             Expression : initiële waarde van de variable
 |             Boolean    : constante ?
 | OUTPUT    : - 
 | RETURN    : een variable
 | DATE      :
 |
 | ABSTRACT  : Constructor van een variable object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Variable::Variable (char *a,
                    int c, 
                    Expression *d, 
                    Expression *e, 
                    Boolean f)
{ 
   Name = a ;
   ReadOnly = f ;
   ClassVar = d ;
   Init = e ;
   index = c ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::Variable
 | INPUT     : char  : naam van de variable
 |             int   : index van de variable
 | OUTPUT    : -
 | RETURN    : variable object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Variable::Variable (char *a,
                    int c )
{ 
   Name     = a ;
   ReadOnly = FALSE ;
   ClassVar = NULL ;
   Init     = NULL ;
   index    = c ;

   if ( index == -2 ) ClassVar = new ConstRef( new rest_list) ;
}  

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::Variable
 | INPUT     : char  : naam van de variable
 | OUTPUT    : -
 | RETURN    : variable object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Variable::Variable(char *a)
{ 
   Name     = a ;
   index    = -1 ;
   Init     = NULL ;
   ReadOnly = FALSE ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::Variable
 | INPUT     : char       : naam van de variable
 |             Expression : type van de variable
 | OUTPUT    : -
 | RETURN    : variable object
 | DATE      :
 |
 | ABSTRACT  : Constructor van een variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Variable::Variable(char *a, Expression *d)
{ 
   Name        = a ;
   index       = -1 ;
   Init        = NULL ;
   ReadOnly    = FALSE ;
   ClassVar    = d ;
   Value       = new DylanObject ;
   Initialized = TRUE ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::GetType
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : type van de variable
 | DATE      :
 |
 | ABSTRACT  : Ophalen van het type van de variable (we stellen
 |             de evaluatie van het type van de variable zolang
 |             mogelijk uit).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Expression *Variable::GetType()
{
   return ClassVar ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::GetName
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : naam van de variable
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de naam van de variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
char *Variable::GetName() 
{ 
   return Name ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : IsConstant
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : TRUE : variable is een constante
 |             FALSE : variable is geen constante
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean Variable::IsConstant() 
{ 
   return ReadOnly ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::GetValue
 | INPUT     : Environment : de omgeing in dewelke we de waarde van
 |                           de variable gaan opzoeken
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Opzoeken van de waarde van een variable binnen een
 |             bepaalde omgeving.
 |             Indien niet geinitialiseerd gaan we eerst de expressie
 |             evalueren en binden in de omgeving
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Variable::GetValue(Environment *Env) 
{ 
   if ( ! Initialized  )
   {
      Value = Init->GetValue(Env) ; // evaluatie expressie
      Env->SetNewBinding( this, Value ) ;
      Initialized = TRUE ;
   }
   else
   {
      Value = Env->GetBinding(this) ;
   }
   if ( index > -1 )
   {
      if ( index <= Value->Size() )
      {
         Value = Value->GetElement( index - 1 ) ;
      }
      else
      {
         Value = false_object ;
      } 
   }
   return Value ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::SetVar
 | INPUT     : Expression : een expressie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van de init expressie van een variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void  Variable::SetVar( Expression *exp ) 
{ 
   Initialized = FALSE ;
   Init = exp ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::SetValue
 | INPUT     : Environment : een omgeving
 |             DylanObject : een waarde
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Wijzigen van de waarde van een variable binnen een
 |             bepaalde omgeving.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void  Variable::SetValue( Environment *Env ,DylanObject *o ) 
{ 
   Initialized = TRUE ;
   Value = o ;
   Env->SetBinding( this, o ) ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Variable::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Variable::Print(int *indent) 
{ 
   if ( ! IsLocal() && ! ReadOnly ) printf( "define variable %s ", Name ) ;
   if ( ! IsLocal() && ReadOnly ) printf( "define constant %s ", Name ) ;
   if ( IsLocal()) printf( "let %s ", Name ) ;
   if ( ClassVar != NULL )
   {
      printf( " :: %s", ClassVar->GetValue(NULL)->GetName() ) ;
   }
   printf( " = " ) ;
   Init->Print(indent) ;
   printf( " ;" ); 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Datadictionnary::GetVar
 | INPUT     : - 
 | OUTPUT    : -
 | RETURN    : Variable
 | DATE      :
 |
 | ABSTRACT  : Ophalen van een variable uit een data dictionnary
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Variable *DataDictionnary::GetVar() 
{ 
    return SymbolList->Var ;
} ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : DataDictionnary::DataDictionnary
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een datadictionnary
 | DATE      :
 |
 | ABSTRACT  : Constructor van een datadictionnary
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DataDictionnary::DataDictionnary()
{
   SymbolList = new DataStruct ;
   SymbolList->next = NULL ;
   SymbolList->prev = NULL ;
   TopOfList  = SymbolList ;
   EndOfList  = SymbolList ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Datadictionnary::InsertVar
 | INPUT     : Variable : een variable
 |             int      : de scope van die variable
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Toevoegen van een variable aan de datadictionnary
 |             rekening houdende met de scope
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void DataDictionnary::InsertVar( Variable *Var, int VarScope) 
{
   struct DataStruct *Item ;

   Item = new DataStruct ;
   Item->next = NULL ;

   while ( SymbolList->next != NULL )
   {
      SymbolList = SymbolList->next ;
   }

   Item->prev        = SymbolList ;
   SymbolList->Var   = Var ;
   SymbolList->Scope = VarScope ;
   SymbolList->next  = Item ;
   SymbolList        = Item ;
   EndOfList         = SymbolList ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DataDictionnary::SearchVar
 | INPUT     : Variable : een variable
 |             VarScope : een scope
 | OUTPUT    : -
 | RETURN    : TRUE : variable gevonden
 | DATE      :
 |
 | ABSTRACT  : Opzoeken van een variable binnen een gegeven scope
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean DataDictionnary::SearchVar( Variable *Var, int VarScope ) 
{
   struct DataStruct *Item ;
   int LocalScope ;

   LocalScope = VarScope ;
   Item = EndOfList->prev ;
   while ( Item != NULL )
   {
      if ( Item->Scope < VarScope ) LocalScope = Item->Scope ;
      SymbolList = Item ;
      if ( ( strcmp(Item->Var->GetName(),Var->GetName()) == 0) &&
           ( Item->Scope == LocalScope )) 
      {
         return TRUE ;
      }
      Item = Item->prev ;
   }
   return FALSE ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : DataDictionnary::Dump
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Dumpen van de datadictionnary (debug)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void DataDictionnary::Dump( ) 
{
   struct DataStruct *Item ;

   Item = TopOfList ;
   printf ("\nVariable dictionnary dump\n" ) ;   
   while ( Item->next != NULL )
   {
      printf ( "Variable = %s (%d) { ", Item->Var->GetName(), Item->Scope ) ;
      Item->Var->Dump() ;
      printf ( " }\n" ) ;
      Item = Item->next ;
   }
}
