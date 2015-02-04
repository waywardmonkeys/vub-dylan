#include "apply.h"
#include "list_type.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : apply
 | INPUT     : DylanObject : een operand
 |             Environment : de omgeving van de operand
 |             P           : de parameters van de operand
 |             Arg         : de argumenten in array vorm (als objecten)
 |             List<Arg>   : de argumenten in lijst vorm ( als
 |                           expressies )
 | OUTPUT    : -
 | RETURN    : resultaat van de oproep is een object.
 | DATE      : 18/01/1995
 |
 | ABSTRACT  : Het uitvoeren van een methode gebeurt in 3 stappen :
 |             1) als de uit te voeren operand een lambda functie is
 |                dan wordt de omgeving van de lambda fct. genomen.
 |                Anders zoeken we de functie op in de dictionnary.
 |             2) indien de functie een primitive is dan wordt de 
 |                functie uitgevoerd met als parameters de Args
 |                Anders worden parameters gelijk gesteld aan de 
 |                List<Arg>. (Dit komt omdat we variable aantal
 |                argumenten en keywords kunnen hebben ).
 |             3) Eventueel nakijken of de return types van de 
 |                methode wel klopt.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *apply( DylanObject *operand, 
                    Environment *Env ,
                    List<DylanObject *> *P,
                    DylanObject **Arg,
                    List<Argument *> *Arguments )
{
   char *func ;
   int i ;
   Method *FuncMethod ;
   Body  *FuncBody ;
   List<Parameter *> *ParList ;
   List<Variable *>  *VarList ;
   static DylanObject *X ;
   static Environment *NewEnv ;

   List<DylanObject *> *Rest = NULL ;
   List<DylanObject *> *Next = NULL ;
   List<DylanObject *> *Keys = NULL ;

   X = new DylanObject ;
   NewEnv = new Environment(Env) ;

   func = new char[255] ; 
   Rest = new List<DylanObject *> ;
   Next = new List<DylanObject *> ;
   Keys = new List<DylanObject *> ;

   // ophalen naam methode
   operand->Getter(func) ;

   // is dit een lambda functie ?
   if ( strcmp(operand->GetName(), "<function>") == 0 )
   {
      Environment *AnEnv ;

      AnEnv = NULL ;
      FuncMethod = operand->GetBody() ;
      if ( FuncMethod->CheckTypes( P, Rest, Keys, Next ) )
      {
         AnEnv = operand->GetEnv() ;
      }
      else
      {
         printf( "anonymous method is wrong ! \n" ) ;
         return NULL ;
      }
      if ( AnEnv != NULL ) NewEnv = AnEnv ;
   }
   // indien nee, opzoeken in dictionary
   else if ( MethodDict.SearchMethod( func, P, Rest, Keys, Next )) 
   {
      delete func ;
      FuncMethod = MethodDict.GetMethod() ;
   }

   // we hebben niks gevonden.
   if ( FuncMethod == NULL ) return NULL ;

   ParList = FuncMethod->GetParameters() ;
   if ( FuncMethod->Primitive() != NULL )
   {
      // deze functie is een primitive.
       
      i = P->GetSize() ;
      if ( Rest != NULL )
      {
        Arg[++i] = new list(Rest) ;
      } 
      if ( ParList == NULL ) return (FuncMethod->Primitive()) () ;
      switch ( FuncMethod->GetParameters()->GetSize() )
      {
      case 1 : 
         return ((FuncMethod->Primitive()) (Arg[1])) ;
      case 2 : 
         return ((FuncMethod->Primitive()) (Arg[1], Arg[2])) ;
      case 3 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3]) ;
      case 4 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3], Arg[4]) ;
      case 5 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3], Arg[4],Arg[5]) ;
      case 6 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3], Arg[4],Arg[5],Arg[6]) ;
      case 7 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3], Arg[4],Arg[5],Arg[6],Arg[7]) ;
      case 8 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3], Arg[4],Arg[5],Arg[6],Arg[7],Arg[8]) ;
      case 9 : 
         return (FuncMethod->Primitive()) (Arg[1], Arg[2], Arg[3], Arg[4],Arg[5],Arg[6],Arg[7],Arg[8],Arg[9]) ;
      default : break ;
     }
   }
   else 
   {
     // binding van de argumenten aan de parameters in de nieuwe
     // omgeving.
     for ( i = 1; ParList != NULL && i <= ParList->GetSize(); i++ )
     {
        ParList->MoveTo(i) ;
        if ( ParList->GetItem()->ParaType() == normal )
        {
            NewEnv->SetNewBinding(ParList->GetItem(), Arg[i] ) ;
        }
        else if ( ParList->GetItem()->ParaType() == rest_par )
        {
           NewEnv->SetNewBinding(ParList->GetItem(), new list(Rest) ) ;
        }
        else if ( ParList->GetItem()->ParaType() == key_par )
        {
           Arguments->MoveTo(i) ;
           ParList->GetItem()->SetVar( Arguments->GetItem()->GetExpression() ) ;
        }
        if ( ParList->GetItem()->ParaType() == singleton )
        {
           ParList->GetItem()->SetValue( NewEnv, Arg[i] ) ;
        }
    }
    FuncBody = new Body(FuncMethod->GetBody() ) ;
    X = FuncBody->GetValue(NewEnv) ;

    // testen of de return values we overeenkomen

    if ( FuncMethod->GetVarList() != NULL )
    {
       VarList = FuncMethod->GetVarList() ;
       if ( VarList->GetSize() != 1 && VarList->GetSize() != X->Size() )
       {
            error( "Not enough return values" ) ;
       }
       else if ( VarList->GetSize() == 1 )
       {
          VarList->MoveTo(1) ;
          if ( (strcmp(VarList->GetItem()->GetType()->GetValue(Env)->GetName(),
                X->GetName()) != 0) && 
                (strcmp(VarList->GetItem()->GetType()->GetValue(Env)->GetName(),
                     "<rest>")) != 0 )
          {
               error( "Return type doesn't match !" ) ;
          }
       }
       else
       {
          for( i = 1; i <= VarList->GetSize(); i++ )
          {
             VarList->MoveTo(i) ;
             if ( (strcmp(VarList->GetItem()->GetType()->GetValue(Env)->GetName(),
                    X->GetElement(i - 1)->GetName()) != 0) && 
                    (strcmp(VarList->GetItem()->GetType()->GetValue(Env)->GetName(),
                         "<rest>")) != 0 )
             {
                  error( "Return type doesn't match !" ) ;
             }
       }
       }
    }
    delete FuncBody ;

    if ( X != NULL && strcmp( X->GetName(), "<function>") == 0 )
    {
        // indien onze return waarde een functie is , dan houden
        // we de omgeving bij, bij die functie
        
        X->SetEnv( NewEnv ) ;
    }
    return X ;
  }

  return NULL ;
}
