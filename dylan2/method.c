/*
 +------------------------------------------------------------------
 | FILENAME  : method.c
 | DATE      : 21/01/1995
 |
 | ABSTRACT  : Bevat een aantal functies om met methoden te werken
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include <stdio.h>
#include "class.h"
#include "method.h"
#include "primitive.h"
#include <stdlib.h>
#include <string.h>

MethodDictionnary MethodDict ; // globale method dictionnary
/*
 +------------------------------------------------------------------
 | FUNCTION  : Method::GetName()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Naam methode
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de naam van de methode
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
char *Method::GetName() 
{ 
   return Name ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Method::Print
 | INPUT     : int : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een methode
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void Method::Print(int *indent)
{ 
   int i ;

   if ( Name != NULL )
   {
     if ( MethodBody != NULL )
     {
        printf( "define method %s ", Name) ;
     }
     else
     {
        printf( "define generic %s ", Name) ;
     }
   }
   else
   {
     printf ( "method " );
   }
   printf( "( ");

   for ( i = 1 ; Parameters != NULL && i <= Parameters->GetSize(); i++ )
   {
      Parameters->MoveTo(i) ;
      switch (Parameters->GetItem()->ParaType() )
      {
      case normal:
         printf( "") ;
         break ;
      case next_par:
         printf( "#next ") ;
         break ;
      case rest_par:
         printf( "#rest ") ;
         break ;
      case key_par:
         printf( "#key ") ;
         break ;
      case all_keys_par:
         printf( "#all-keys ") ;
         break ;
      default:
         break ;
      };

      printf( "%s ", Parameters->GetItem()->GetName()) ;
      if ( Parameters->GetItem()->GetType() != NULL )
      {
         printf( " :: %s" ,Parameters->GetItem()->GetType()->GetValue(NULL)->GetName()) ;
      }
      if ( i != Parameters->GetSize() ) printf( ", ") ;
   }
   printf( ")\n" ) ;

   if ( VarList != NULL )
   {
      printf( " => ( " ) ;
      for ( i = 1 ; i <= VarList->GetSize(); i++ )
      {
         VarList->MoveTo(i) ;
         printf( "%s ", VarList->GetItem()->GetName()) ;
         if ( VarList->GetItem()->GetType() != NULL )
         {
            printf( " :: %s ",VarList->GetItem()->GetType()->GetValue(NULL)->GetName()) ;
         }
         if ( i != VarList->GetSize() ) printf( ", ") ;
      }
      printf ( ")\n" ) ;
   }

   if ( MethodBody ) 
   {
      *indent += 5 ;
      MethodBody->Print(indent) ;
      *indent -= 5 ;
      printf ("end method ; \n" ) ;
   }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : operator <
 | INPUT     : Methode
 | OUTPUT    : -
 | RETURN    : > 0 : m1 < m2
 |             < 0 : m1 > m2
 |             = 0 : m1 = m2
 | DATE      :
 |
 | ABSTRACT  : Test of methode m1 < methode m2
 |             2 methoden zijn kleiner als de klassen  van hun 
 |             respectievelijke parameters kleiner zijn
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int Method::operator < ( Method &M1)
{
    List<Parameter *> *P1 ;  // parameters methode m1
    List<Parameter *> *P2 ;  // parameters methode m2
    DylanObject       *D1 ;
    DylanObject       *D2 ;
    DylanObject      **Cpl ; // class precedence list

    int  i ;
    int  j ;
    int  waarde = 0 ;
    int  Size ;

    P1 = M1.GetParameters() ;
    P2 = this.GetParameters() ;

    for( i = 1; P1 != NULL && i <= P1->GetSize() ; i++ )
    {
       P1->MoveTo(i) ;
       P2->MoveTo(i) ;

       // enkel 'normale' parameters komen in aanmerking
       // (dus geen key of rest parameters)

       if ( (P1->GetItem()->ParaType() == normal) &&
            (P2->GetItem()->ParaType() == normal))
       {
          if ( strcmp( P1->GetItem()->GetType()->GetValue(NULL)->GetName(),
                       P2->GetItem()->GetType()->GetValue(NULL)->GetName() ) == 0)
          {
              // klassen van de parameters gelijk
              waarde += 0 ;
          }
          else
          {
             D1 = P1->GetItem()->GetType()->GetValue(NULL) ;
             D2 = P2->GetItem()->GetType()->GetValue(NULL) ;

             Cpl = D1->GetSuperclass(&Size) ;
             for( j = Size - 1; j >= 0; j-- ) 
             {
                D1 = Cpl[j] ; // jde klasse uit de class precedence list
                if ( D1 != NULL )
                {
                   if ( strcmp( D1->GetName(), D2->GetName() ) == 0 )
                   {
                      // als het type van de parameter van m2
                      // in de cpl zit van methode m1 dan is parameter
                      // i van m1 'groter' dan die van m2
                      waarde += 1 ; 
                      break ;
                   }
                }
             }
             if ( j == -1 ) waarde += -1 ;
          }
       }
       else if ( P2->GetItem()->ParaType() == singleton )
       {
          // parameter van p2 is een singleton
          waarde += -1 ;
       }
       else if ( P1->GetItem()->ParaType() == singleton )
       {
          // parameter van p1 is een singleton
          waarde += 1 ;
       }
    } 
    return waarde ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : Method::CheckTypes
 | INPUT     : List<DylanObject *> : een lijst van input waarden
 | OUTPUT    : List<DylanObject *> : rest parameters
 |             List<DylanObject *> : key parameters
 |             List<DylanObject *> : next parameter
 | RETURN    : TRUE : methode mag uitgevoerd worden op deze 
 |                    input waarden.
 | DATE      :
 |
 | ABSTRACT  : Testen of de argumenten lijst van de methode 
 |             klopt met de input waarden
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean Method::CheckTypes( List<DylanObject *> *Objects,
                            List<DylanObject *> *RestList,
                            List<DylanObject *> *KeysList,
                            List<DylanObject *> *NextList ) 
{
   List<DylanObject *> *TypePara ;
   int                  Ok ;
   int                  i ;
   int                  j ;
   int                  NbrPara1 = 0 ;
   int                  NbrPara2 = 0;
   int                  Size ;
   Boolean              rest ;
   Boolean              keys ;
   DylanObject         **Superclass_object ;

   TypePara = new List<DylanObject *> ;

   if ( Objects == NULL ) return TRUE ;

   if ( Parameters != NULL ) NbrPara1 = Parameters->GetSize() ;
   NbrPara2 = Objects->GetSize() ;

   // indien er minder objecten zijn dan parameters --> methode 
   // is niet aanvaardbaar.
   
   if ( NbrPara2 < NbrPara1 ) return FALSE ;
   
   Ok = 0 ;
   rest = FALSE ;
   keys = FALSE ;
   j    = 1 ;
   for( i = 1; i <= NbrPara1 ; i++ )
   {
      Parameters->MoveTo(i) ;
      Objects->MoveTo(j) ;

      if (Parameters->GetItem()->ParaType() == rest_par ) rest = TRUE ;

      if ((Parameters->GetItem()->ParaType() == key_par ||
          Parameters->GetItem()->ParaType() == all_keys_par) )
      {
         rest = FALSE ;
         keys = TRUE ;
         if ( strcmp( Objects->GetItem()->GetName(), "<keyword>") != 0 )
         {
           for( j++ ;
                j <= NbrPara2 &&
                strcmp( Objects->GetItem()->GetName(), "<keyword>") != 0;
                j++ )
           {
              RestList->AppendItem( Objects->GetItem() ) ;
              Objects->MoveTo(j) ;
              Ok++ ;
           }
           j-- ;
         }
      }
      if (Parameters->GetItem()->ParaType() == next_par )
      {
          if ( NextList == NULL ) NextList = new List<DylanObject *> ;
          NextList->AppendItem( Objects->GetItem() ) ;
          // Objects->Delete() ;
          Ok++ ;
      }
      else if ( rest )
      {
          if ( RestList == NULL ) RestList = new List<DylanObject *> ;
          RestList->AppendItem( Objects->GetItem() ) ;
          Objects->Delete() ;
          Ok++ ;
      }
      else if ( keys )
      {
         char s[255] ;
         DylanObject *o2 ;
         int length ;
         char  *k ;

         k = Parameters->GetItem()->GetKeyword() ;
         length = strlen(k) - 1 ;
         o2 = Objects->GetItem() ;
         o2->Getter(s) ;

         if ( k[length] != ':' )
         {
            if ( strncmp ( k, s, length) == 0 )
            {
               Ok++ ;
            }             
         }
         else if ( strcmp ( k, s) == 0 )
         {
            Ok++ ;
         }             
         j++ ;
      }
      else if (Parameters->GetItem()->ParaType() == normal ) 
      {
         TypePara->AppendItem( Parameters->GetItem()->GetType()->GetValue(NULL) ) ;
         // als het type van mijn object dat ik doorgeef een symbool is
         // dan laat ik het toch door, want dit zou kunnen betekenen dat
         // het een functie is dat later zal naar boven komen.
         if ( (strcmp( Objects->GetItem()->GetName(), "<symbol>") == 0) ||
              strcmp ( Parameters->GetItem()->GetType()->GetValue(NULL)->GetName(),
                       Objects->GetItem()->GetName() ) == 0 ) 
         {
            Ok++ ;
         } 

         j++ ;
      }
      else if (Parameters->GetItem()->ParaType() == singleton ) 
      {
         DylanObject *o1 ;
         DylanObject *o2 ;
         Expression  *e ;
         Environment *Env ;
         Boolean      Bool ;

         o1 = Parameters->GetItem()->GetSingleton()->GetValue(NULL) ;
         o2 = Objects->GetItem() ;
         e = new Eq( new ConstRef(o1), new ConstRef(o2) ) ;
         Env = new Environment( the_global_environment ) ;
         MethodDict.SaveState() ;
         e->GetValue(Env)->Getter(&Bool) ;
         MethodDict.RestoreState() ;
         delete e ;
         delete Env ;
         if ( (strcmp ( o1->GetName(), o2->GetName() ) == 0) &&
              ( Bool ) )
         {
            Ok++ ;
         }
         j++ ;     
      }
   }

   i = Objects->GetSize() ;

   for ( ;j <= i ; j++ )
   {
      if ( rest )
      {
          if ( RestList == NULL ) RestList = new List<DylanObject *> ;
          RestList->AppendItem( Objects->GetItem() ) ;
          Objects->Delete() ;
          Ok++ ;
      }
      else if ( keys )
      {
      }

   }
   NbrPara1 = TypePara->GetSize() ;

   if ( Ok == NbrPara2 )
   { 
      return TRUE ;
   }

   /* nu zoeken of de superclasses matchen */
   Ok = 0 ;

   for ( i = 1 ; i <= NbrPara1 ; i++ )
   {
      Objects->MoveTo(i) ;
      TypePara->MoveTo(i) ;
      /* eerst testen of de klassen wel matchen */
      if ( strcmp ( TypePara->GetItem()->GetName(), Objects->GetItem()->GetName() ) == 0 )
      {
         Ok++ ;
      }
      else
      {
          /* nu doen we verder met de superklassen van dit object */
         Superclass_object = Objects->GetItem()->GetSuperclass(&Size) ;
         for( j = Size - 1; j >= 0; j-- )
         {
            if ( strcmp(TypePara->GetItem()->GetName(), Superclass_object[j]->GetName()) == 0 ) 
            {  
               Ok++ ;
               break ;
            }
         }
      }
   }
   if ( NbrPara1 > 0 ) TypePara->MoveTo(1) ;
   if ( Ok == NbrPara1 && (NbrPara1 == NbrPara2 || rest ) ) 
   { 
      return TRUE ;
   }
   return FALSE ;
} ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::GetMethod
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Method * : de uittevoeren methode
 | DATE      :
 |
 | ABSTRACT  : Ophalen uit een gesorteerde vector van methoden
 |             de methode die moet uitgevoerd worden
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Method *MethodDictionnary::GetMethod() 
{ 
    if ( *MethodsToSort == 0 )
    {
       error( "No applicable methods found !\n" ) ;
    }
    if ( *MethodIndex == *MethodsToSort - 1 )
    {
       // er is maar 1 methode
       return SortArray[*MethodIndex] ;
    }
    else 
    {
       if ( *(SortArray[*MethodIndex]) < *(SortArray[*MethodIndex + 1]) )
       {
          return SortArray[(*MethodIndex)++] ;
       }  
       else
       {
          // methoden zijn gelijk == ambigu
          printf( "Ambiguous method call ! \n" );
          return NULL ;
       }
    }
} ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::MethodDictionnary
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Een methode dictionnary
 | DATE      :
 |
 | ABSTRACT  : Constructor van een methode dictionnary
 |
 | CHANGES   : 9 Feb 1995 : Aanpassen van de methode dictionnary
 |             zodat het reentrable is, daarvoor gebruiken we een
 |             stack om de interne status van de dictionnary te 
 |             saven.
 +------------------------------------------------------------------
 */
MethodDictionnary::MethodDictionnary()
{
   SymbolList = new MethodDict ;
   SymbolList->next = NULL ;
   SymbolList->Meth = NULL ;
   TopOfList  = SymbolList ;
   States     = new List<State *> ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::InsertMethod
 | INPUT     : Method : een bepaalde methode
 |             int    : de scope van de methode
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Invoegen van een methode in de dictionnary
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void MethodDictionnary::InsertMethod( Method *M, int AScope) 
{
   struct MethodStruct *Item ;
   int    NbrParam ;

   Item = new MethodStruct ;
   Item->next = NULL ;
   Item->prev = NULL ;
   Item->Meth = M ;
   Item->scope = AScope ;

   SymbolList = TopOfList ;

   while (  strcmp( SymbolList->Name, M->GetName()) != 0  &&
            SymbolList->next != NULL )
   {
      SymbolList = SymbolList->next ;
   }
   if ( SymbolList->next == NULL )
   {
       SymbolList->next = new MethodDict ;
       strcpy( SymbolList->Name, M->GetName() ) ;
       SymbolList->Meth = Item ;
       SymbolList = SymbolList->next ;
   }
   else
   {
      while ( SymbolList->Meth->next != NULL )
           SymbolList->Meth = SymbolList->Meth->next ;
      Item->prev = SymbolList->Meth ;
      SymbolList->Meth->next = Item ;
      SymbolList->Meth = SymbolList->Meth->next ;
   }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : SortMethod
 | INPUT     : Method : een methode
 |             Method : een methode
 | OUTPUT    : -
 | RETURN    :
 | DATE      :
 |
 | ABSTRACT  : Dit is een wrapper functie , voor de qsort
 |             system call die de gevonden methoden sorteert 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int SortMethod( Method **M1, Method **M2 )
{
   return ((Method) **M1 < (Method ) **M2) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::SearchMethod
 | INPUT     : char * : naam van de methode
 |           : List<DylanObject *> : input waarden
 | OUTPUT    : List<DylanObject *> : rest waarden
 |             List<DylanObject *> : keywords
 |             List<DylanObject *> : next list
 | RETURN    :
 | DATE      :
 |
 | ABSTRACT  : Opzoeken van alle methoden uit de methoddictionnary
 |             die kandidaten zijn  voor een mogelijke oproep
 |             en sorteren van meest specifieke methode naar minst
 |             specifieke.
 |             (Later moet er nog een functie bijkomen die het mogelijk
 |             moet maken om door de gesorteerde array te lopen).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Boolean MethodDictionnary::SearchMethod( char *Name, 
                                         List<DylanObject *> *Objects,
                                         List<DylanObject *> *RestList,
                                         List<DylanObject *> *KeysList,
                                         List<DylanObject *> *NextList ) 
{
   struct MethodDict *Item ;
   struct MethodStruct *Item2 ;
   int i ;

   Item = TopOfList ;
   SortArray = new (GC) Method * [100] ;
   MethodsToSort = new (GC) int ;
   MethodIndex   = new (GC) int ;
   *MethodsToSort = 0 ;
   Item2 = NULL ;

   while ( Item->next != NULL )
   {
      SymbolList = Item ;
      if ( strcmp(Item->Name,Name) == 0)
      {
         Item2 = Item->Meth ;
         break ;
      }
      Item = Item->next ;
   }

   if ( Item2 != NULL )
   {
      while ( Item2->prev != NULL ) Item2 = Item2->prev ;
      
      while ( Item2 != NULL )
      {
         if ( TheDylanScope >= Item2->scope &&
              Item2->Meth->CheckTypes(Objects, RestList, KeysList, NextList) )
         { 
             SortArray[(*MethodsToSort)++] = Item2->Meth ;            
         }
         Item2 = Item2->next ;
      }
   }

   *MethodIndex   = 0 ;
   if ( *MethodsToSort > 0 )
   {
      qsort(SortArray, *MethodsToSort, sizeof(Method *) , SortMethod ) ;

      return TRUE ;
   }
   return TRUE ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::Dump
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Dumpen van de dictionnary (dit is voor debug redenen).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void MethodDictionnary::Dump()
{
   struct MethodDict *Item ;
   struct MethodStruct *TopMeth ;

   int i = 0 ;
   int j ;
   List<Parameter *> *P ;

   Item = TopOfList ;
   
   while ( Item->next != NULL )
   { 
      SymbolList = Item ;
      i++ ;
      printf ( "item : %d = %s \n",  
                        i, Item->Name ) ;

      while( Item->Meth->prev != NULL )
            Item->Meth = Item->Meth->prev ;
      TopMeth = Item->Meth ;

      for( ; Item->Meth != NULL; Item->Meth = Item->Meth->next )
      {
         P = Item->Meth->Meth->GetParameters() ;
         printf( "       (" ) ;
         for( j = 1; j <= P->GetSize(); j++ )
         {
            P->MoveTo(j) ;
            if ( P->GetItem()->ParaType() == normal )
                 printf( " %s ", P->GetItem()->GetType()->GetValue(NULL)->GetName())  ;
            if ( j != P->GetSize() ) printf( "," ) ;
         }
         printf( ")\n") ;
      }
      Item->Meth = TopMeth ;
      Item = Item->next ;
   }
} ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::SaveState()
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Bewaren van de internal state van de method-
 |             dictionnary (voor rentrance)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void MethodDictionnary::SaveState()
{
   State *S ;
   S = new State ;
   S->SArray = SortArray ;
   S->MaxSort = MethodsToSort ;
   S->AnIndex = MethodIndex ;
   States->AppendItem(S) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MethodDictionnary::RestoreState
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Terugkeren naar een vorige status
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void MethodDictionnary::RestoreState()
{
   State *S ;
   S = States->GetItem() ;
   States->Delete() ;
   SortArray = S->SArray ;
   MethodsToSort = S->MaxSort ;
   MethodIndex = S->AnIndex ;
}
