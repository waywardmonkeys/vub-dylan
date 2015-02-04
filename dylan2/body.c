/*
 +------------------------------------------------------------------
 | FILENAME  : body.c
 | DATE      : 01/11/1994
 |
 | ABSTRACT  : Body = { constituenten }
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include <stdio.h>

#include "body.h"
#include "types.h"
#include "object.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : strrpt
 | INPUT     : char * : target string
 |             char c : het karater dat moet herhaalt worden.
 |             int  l : aantal keren
 | OUTPUT    : een string met 'c' l-keer herhaalt.
 | RETURN    : -
 | DATE      : 01/09/1994
 |
 | ABSTRACT  : Dit is een string repeat functie, zit eigenlijk niet
 |             op de juiste plaats.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void strrpt( char *s, char c, int l )
{
   int i ;

   for( i = 0 ; i < l; i++ )
   {
     s[i] = c ;
   }
   s[l] = '\0' ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Body::AppendConstituent
 | INPUT     : Constituent * : een constituent
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Toevoegen van een constituent aan een body.
 |             De structuur van een body is een gewone gelinkte 
 |             lijst.
 |             constituent = { def. vorm, expression }
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Body::AppendConstituent( Constituent *C ) 
{ 
   AProgram->C = C ;     
   AProgram->next = new (GC) BodyStruct ;
   AProgram->next->prev = AProgram ;
   if ( Top == NULL ) Top = AProgram ;
   AProgram = AProgram->next ;
   AProgram->next = NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Body::Print
 | INPUT     : int * : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Pretty (?) print van een body, ook genoemd
 |             de unparser.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Body::Print(int *indent) 
{ 
   char *IndentStr ;

   AProgram = Top ; 

   IndentStr = new char [*indent + 1 ] ;
   strrpt( IndentStr, ' ', *indent ) ;
   printf( "%s", IndentStr ) ;
   while ( AProgram->next != NULL )
   { 
        AProgram->C->Print(indent) ;
        printf( "\n%s", IndentStr ) ;
        AProgram = AProgram->next ;
   }
   delete IndentStr ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Body::Body
 | INPUT     : Body * : een body
 | OUTPUT    : 
 | RETURN    : een copy van de body
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Dit is een copy constructor voor bodies,
 |             wordt voornamelijk gebruikt voor lambda's en
 |             closures (of in dylan terminologie : anonieme
 |             methoden en omgevingen )
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Body::Body(const Body *B) 
{ 
   struct BodyStruct *Local ;

   if ( B != NULL )
   {
      Local = B->Top ;

      this->AProgram = new (GC) BodyStruct ;
      this->AProgram->next = NULL ;
      this->AProgram->prev = NULL ;
      while ( Local->next != NULL )
      { 
           this->AppendConstituent(Local->C) ;
           Local = Local->next ;
      }
   }
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : Body::GetValue()
 | INPUT     : Environment : omgeving in dewelke we de waarde van
 |                           een body opvragen.
 | OUTPUT    : -
 | RETURN    : een object, ( elke body returnt iets, indien niks wordt
 |             teruggegeven dan wordt het false_object teruggestuurd )
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : We doorlopen de lijst van voor naar achter en we
 |             dispatchen de 'getvalue' naar de constituenten.
 |             (d.i. het zogenaamde ambtenarenalgoritme, het is 
 |             niet ik maar die onder mij ).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *Body::GetValue(Environment *Env) 
{ 
   DylanObject *R ;

   AProgram = Top ;

   TheDylanScope++ ;
   while ( AProgram->next != NULL )
   { 
        if ( AProgram->C->IsLocal() ) AProgram->C->ReEval(Env) ;

        R = AProgram->C->GetValue(Env) ;

        AProgram = AProgram->next ;
   }
   TheDylanScope-- ;
   return R ;
} 
