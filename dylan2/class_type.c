#include "class_type.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::class_type
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een object van het type 'class'
 | DATE      : 01/01/1995
 |
 | ABSTRACT  : Dit is een default constructor, om bepaalde 
 |             spullen bij default te initialiseren.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
class_type::class_type()
{
   id = "<class>" ;
   Superclass = new DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::class_type
 | INPUT     : char *              : naam van de klasse
 |             List<DylanObject *> : superclasses van deze klasse
 |             List<Slot_specs *>  : de slots van deze klasse
 | OUTPUT    : -
 | RETURN    : een instance van een klasse
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
class_type::class_type(char *s, 
                       List<DylanObject *> *L1, 
                       List<Slot_specs *> *L2) 
{ 
   int i ;

   id = s ; 
   Slots = L2 ;
   NbrSuperclasses = L1->GetSize() ;
   Superclass = new DylanObject * [L1->GetSize()] ;
   for( i = 0 ; i < L1->GetSize(); i++ )
   {
     L1->MoveTo(i+1) ;

     Superclass[i] = L1->GetItem() ;
   }
   ClassAdj = open_class ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::class_type
 | INPUT     : DylanObject * : de klasse die moet gecopieerd worden
 |             List<Slot_specs *> : de slots van de klasse
 |             List<DylanObject *> : initialisatie waarden (= keywords)
 | OUTPUT    :
 | RETURN    :
 | DATE      :
 |
 | ABSTRACT  : Dit is een copy constructor, maar dan wel een speciale
 |             hij doet namelijk een deep copy.
 |             Er kunnen een aantal keywords meegegeven om de copie
 |             met andere waarden te initialiseren.
 |             We moeten een deep copie doen en geen shallow copie
 |             anders krijgen we het effect dat de superclassen allemaal
 |             naar hetzelfde wijzen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
class_type::class_type( DylanObject *X, List<Slot_specs *> *L, List<DylanObject *> *KeywordsList )
{
   int i ;
   DylanObject **Superclasses ;
   int Size ;

   this->id = X->GetName() ;
   Superclasses = X->GetDirectSuperclass(&Size) ;
   this->Superclass = new DylanObject *[Size] ;

   for ( i = 0; i < Size ; i++ )
   {
      if ( Superclasses[i]->GetSlots() != NULL )
      {
         // deep copy de superclass
         this->Superclass[i] = Instance( Superclasses[i], KeywordsList ) ;
      }
      else
      {
         this->Superclass[i] = Superclasses[i] ;
      }
   }

   this->Slots = new List<Slot_specs *> ;

   for( i = 1; i <= L->GetSize() ; i++ ) 
   {
      L->MoveTo(i) ;
      // indien de slot allocatie 'class' is dan geen deep copie
      // = analoog aan class variablelen in Smalltalk of static in C++
      if ( L->GetItem()->GetSlotAllocation() != dylan_class )
      {

         this->Slots->AppendItem( new Slot_specs( L->GetItem()->GetSlotAdjective(),
                                                  L->GetItem()->GetSlotAllocation(),
                                                  L->GetItem()->GetGetterName(),
                                                  L->GetItem()->GetType(),
                                                  L->GetItem()->GetValue(),
                                                  L->GetItem()->GetInitKeyword(),
                                                  L->GetItem()->GetReqInitKeyword() ) ) ;
      }
      else this->Slots->AppendItem( L->GetItem() ) ;
   }
   if ( KeywordsList != NULL )
   {
      this->Initialize(KeywordsList) ; 
   }
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::Instance
 | INPUT     : DylanObject * : class die moet geinstantieerd worden
 |             List<DylanObject *> : initialisatie keywords
 | OUTPUT    : -
 | RETURN    : Een instance van een klasse
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *class_type::Instance(DylanObject *X, List<DylanObject *> *KeywordsList) 
{ 
   int i ;
   static List<Slot_specs *> *L ; 
   List<Property *> *Props ;
   static DylanObject *O ;

   L = new List<Slot_specs *> ;
   if ( strcmp( X->GetName(), "<object>" ) == 0 ) return NULL ;

   if ( X->GetSlots() != NULL )
   {
      *L = *(X->GetSlots());
      O = new class_type( X, L, KeywordsList ) ; 
      return O ;
   }
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::Print
 | INPUT     : int * : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 
 |
 | ABSTRACT  : pretty printer
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void class_type::Print(int *indent)
{ 
   int i ;

   printf( "define class %s ( ", id ) ;
   printf ( " %s ", Superclass[0]->GetName() ) ;
   for( i = 1; i < NbrSuperclasses; i++ )
   {
     printf ( ", %s ", Superclass[i]->GetName() ) ;
   }
   printf( ")\n" ) ;

   for( i = 1; Slots != NULL && i <=Slots->GetSize(); i++ )
   {
     Slots->MoveTo(i) ;
     printf( "   ") ;
     if ( (Slots->GetItem())->GetSlotAdjective() != noadj )
     {
        switch ( (Slots->GetItem())->GetSlotAdjective() )
        {
        case open_slot : printf( "open " ) ;
                         break ;
        case sealed : printf( "sealed " ) ;
                      break ;
        case open_sealed : printf( "open sealed ");
                           break ;
        default: break ;
        }
     }
     if ( (Slots->GetItem())->GetSlotAllocation() != noalloc )
     {
        switch ( (Slots->GetItem())->GetSlotAllocation() )
        {
        case instance : printf( "instance " ) ;
                         break ;
        case dylan_class : printf( "class " ) ;
                      break ;
        case subclass : printf( "each-subclass ");
                           break ;
        case constant_class : printf( "constant ");
                           break ;
        case virtual_class : printf( "virtual ");
                           break ;
        default: break ;
        }
     }
     printf("slot " ) ;
     printf("%s ", (Slots->GetItem())->GetGetterName() ) ;
     if ( (Slots->GetItem())->GetType() != NULL )
          printf( ":: %s ",Slots->GetItem()->GetType()->GetName() )  ;

     if ( (Slots->GetItem())->GetValue() != NULL )
     {
          printf( ", init-value: " ) ;
          Slots->GetItem()->GetValue()->Print(indent) ;
     }

     if ( (Slots->GetItem())->GetSetterName() != NULL )
          printf( ", setter: %s", (Slots->GetItem())->GetSetterName() ) ;

     if ( (Slots->GetItem())->GetInitFunction() != NULL )
     {
          printf( ", init-function: ") ;
          Slots->GetItem()->GetInitFunction()->Print(indent) ;
     }


     if ( (Slots->GetItem())->GetInitKeyword() != NULL )
          printf( ", init-keyword: %s", (Slots->GetItem())->GetInitKeyword()) ;

     if ( (Slots->GetItem())->GetReqInitKeyword() != NULL )
          printf( ", required-init-keyword: %s", (Slots->GetItem())->GetReqInitKeyword()) ;
     printf( "\n" ) ;
   }
   printf( "end class %s\n ", id ) ;
   
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::Initialize
 | INPUT     : List<DylanObject *>
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Initialisatie parameters van een klasse,
 |             De default waarden worden gemaakt op momement van
 |             de parsing van de classe.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void class_type::Initialize(List<DylanObject *> *InitList ) 
{
  int i ;
  int j ;
  char str[255] ;
  int Ok ;
  Boolean ReqKeyword = TRUE ;
  Ok = 0 ;
  for( i = 1; i <= Slots->GetSize(); i++ )
  {
     Slots->MoveTo(i) ;
     for( j = 1; j <= InitList->GetSize(); j++ )
     {
        InitList->MoveTo(j) ;
        InitList->GetItem()->Getter(str) ;
        if (Slots->GetItem()->GetReqInitKeyword() != '\0' )
        {
           ReqKeyword = FALSE ;
           if ( strcmp( str, Slots->GetItem()->GetReqInitKeyword() ) == 0 )
           {
              ReqKeyword = TRUE ;
              Slots->GetItem()->SetValue( ((keyword *) InitList->GetItem())->GetValue(NULL) ) ;
              Ok++ ;
              break ;
           }
        }
        if (Slots->GetItem()->GetInitKeyword() != '\0' )
        {
           if ( strcmp( str, Slots->GetItem()->GetInitKeyword() ) == 0 )
           {
              Slots->GetItem()->SetValue( ((keyword *) InitList->GetItem())->GetValue(NULL) ) ;
              Ok++ ;
              break ;
           }
        }
     }
     if ( ! ReqKeyword )
     {
        error( "Required init keyword needed !" ) ;
     }
  }

}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::ReturnSlot
 | INPUT     : char *s : naam van de slot die men wenst
 | OUTPUT    : -
 | RETURN    : slot van de klasse of NULL
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
Slot_specs *class_type::ReturnSlot(char *s)
{
   int i ;
   int j ;
   int Size ;
   DylanObject **Classes ;
   List<Slot_specs *> *MySlots ;

   MySlots = new List<Slot_specs *> ;
   Classes = this->GetSuperclass(&Size) ; ;
   for( j = Size - 1; j >= 0; j-- )
   {
     *MySlots = *(Classes[j]->GetSlots() ) ;
     for( i = 1; MySlots != NULL && i <= MySlots->GetSize(); i++ )
     {
       MySlots->MoveTo(i) ;
       if ( (strcmp(MySlots->GetItem()->GetGetterName(), s) == 0) &&
            MySlots->GetItem()->GetSlotAdjective() != inherited )
          return MySlots->GetItem() ; 
       if ( (strcmp(MySlots->GetItem()->GetGetterName(), s) == 0) &&
            (MySlots->GetItem()->GetSlotAdjective() == inherited) &&
               (MySlots->GetItem()->GetValue() != NULL ) )
          return MySlots->GetItem() ; 
     }
   }
   error( "Unkown slot getter specified !" ) ;
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::SetClassAdj
 | INPUT     : class_adjectives : het adjective
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Het adjectief van een class kan zijn :
 |             abstract, sealed, open 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void class_type::SetClassAdj( class_adjectives a )
{
   ClassAdj = a ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_type::GetSlots
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : Alle slots van een bepaalde klasse
 | DATE      :
 |
 | ABSTRACT  :
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
List<Slot_specs *> *class_type::GetSlots()
{
   return Slots ;
}

