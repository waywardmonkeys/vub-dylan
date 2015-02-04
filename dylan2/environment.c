/*
 +------------------------------------------------------------------
 | FILENAME  : environment.c
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Implementatie van omgevingen in Dylan
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/

#include "environment.h"
#include "variable.h"
/*
 +------------------------------------------------------------------
 | FUNCTION  : Binding::Binding
 | INPUT     : Variable * : een bepaalde variable
 |             DylanObject : een object
 | OUTPUT    : -
 | RETURN    : een nieuwe binding
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Het binden van een variable aan een bepaald
 |             object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Binding::Binding( Variable *Var, DylanObject *Obj )
{
   V = Var ;
   O = Obj ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Binding::GetVariable
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : De variable kant van een bepaalde binding
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Variable *Binding::GetVariable()
{
   return V ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Binding::GetObject
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : DylanObject
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Teruggeven van het object die gebonden is aan een 
 |             bepaalde variable
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Binding::GetObject()
{
   return O ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Environment::Environment
 | INPUT     : Environment * : een omgeving
 | OUTPUT    : -
 | RETURN    : een nieuwe omgeving
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Een nieuwe omgeving wordt gecreerd met als 
 |             omgeving de omhullende omgeving.
 |             +--------+
 |             | Env1   |--> binding --> binding --> binding --> ...
 |             +--------+
 |                 ^
 |                 |
 |             +--------+
 |             | Env2   |--> binding --> binding --> binding --> ...
 |             +--------+
 |                 ^
 |                 |
 |             +--------+
 |             | Env3   |--> binding --> binding --> binding --> ...
 |             +--------+
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Environment::Environment( Environment *Env )
{
   PrevEnv = Env ;
   Bindings = new List<Binding *> ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Environment::Environment
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Een nieuwe omgeving
 | DATE      :
 |
 | ABSTRACT  : Deze functie wordt normaal 1x opgeroepen namelijk
 |             om de globale omgeving te maken.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Environment::Environment()
{
   PrevEnv = NULL ;
   Bindings = new List<Binding *> ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Environment::SetPrevEnv
 | INPUT     : Environment *
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Het wijzigen van de superenvironment van het
 |             huidige environment.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Environment::SetPrevEnv( Environment *Env )
{
    PrevEnv = Env ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Compare
 | INPUT     : Binding * : een binding
 |             Binding * : een binding
 | OUTPUT    : TRUE : 2 bindings zijn gelijk
 |             FALSE : bindings niet gelijk
 | RETURN    : 
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int Compare( Binding *B1, Binding *B2 )
{
    if ( strcmp(B1->GetVariable()->GetName(), 
                B2->GetVariable()->GetName()) == 0 ) return TRUE ;
    return FALSE ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : Environment::SetBinding
 | INPUT     : Variable * : een variable
 |             DylanObject * : een object
 | OUTPUT    : -
 | RETURN    : TRUE :  altijd , 
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : 1) zoeken of de variable al bestaat in deze omgeving
 |                of de vorige.
 |             2) indien ja wijzigen waarde
 |                indien nee, nieuwe binding creeren en in de 
 |                omgeving brengen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean Environment::SetBinding( Variable *Var, DylanObject *Obj )
{
   List<Binding *> *PtrToBindings ;
   Environment      *PtrEnv ;
   Boolean           found ;
   Binding           *B ;

   PtrEnv = this ;
   B = new Binding( Var, Obj ) ;
   found = FALSE ;

   while ( PtrEnv != NULL && ! found )
   {
      PtrToBindings = PtrEnv->GetBindings() ;
      if ( PtrToBindings->SearchItem( Compare, B ) != -1 )
      {
          PtrToBindings->GetItem()->SetObject( Obj ) ;
          found = TRUE ;
      }
      else
      {
         PtrEnv = PtrEnv->GetPrevEnv() ;
      }
   }
   if ( ! found )
   {
       this->SetNewBinding( Var, Obj )  ;
   }
   delete B ;
   return TRUE ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Environment::SetNewBinding
 | INPUT     : Variable * : een variable
 |             DylanObject * : een objec
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Toevoegen van een binding aan een omgeving
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean Environment::SetNewBinding( Variable *Var, DylanObject *Obj )
{
   Bindings->AppendItem( new Binding( Var, Obj ) ) ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : Environment::GetBinding
 | INPUT     : Variable * :
 | OUTPUT    : -
 | RETURN    : DylanObject, het object dat correspondeert met
 |             de variable
 | DATE      : 10/01/1995
 |
 | ABSTRACT  : Doorlopen van alle omgevinge op zoek naar de 
 |             variable ( van achter naar voor, de meest recente
 |             eerst ).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Environment::GetBinding( Variable *Var )
{
   List<Binding *> *PtrToBindings ;
   Environment      *PtrEnv ;
   Binding          *B ;

   B = new Binding( Var, NULL ) ;

   PtrEnv = this ;
   PtrToBindings = Bindings ;

   while ( PtrEnv != NULL )
   {
      PtrToBindings = PtrEnv->GetBindings() ;
      if ( PtrToBindings->SearchItem( Compare, B ) != -1 )
      {
          delete B ;
          return PtrToBindings->GetItem()->GetObject() ;
      }
      else
      {
         PtrEnv = PtrEnv->GetPrevEnv() ;
      }
   }
   delete B ;
   return NULL ;
}
