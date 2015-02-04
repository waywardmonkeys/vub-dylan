/*
 +------------------------------------------------------------------
 | FILENAME  : primitive.c
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : samenraapsel van allerlei soorten functies, deze
 |             functies werden in C geimplementeerd om aan deze
 |             Dylan implementatie toch ietofwat performantie te
 |             geven.
 |             Sommige functies (zoals de bewerkingen) zorgen voor
 |             de low-level implementatie van bepaalde primitieven
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "primitive.h"
#include "method.h"
#include <stdarg.h>
#include "apply.h"

enum operators { Add, Mul, Div, Sub } ;
enum compare_operators { Eq, Ne, Lt, Gt, Le, Ge } ;
enum coercion { to_int, to_float, to_double  } ;

/*
 +------------------------------------------------------------------
 | FUNCTION  : arithmetic
 | INPUT     : operator : een operator
 |             number   : een getal
 |             number   : een getal
 | OUTPUT    : -
 | RETURN    : een getal
 | DATE      :
 |
 | ABSTRACT  : Basisbewerkingen op getallen, met automatische
 |             coercion van het ene type naar het andere.
 |             Enkel de basisbewerkingen zijn geimplementeerd, alle
 |             andere bewerkingen kan men implementeren in Dylan.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
static DylanObject *arithmetic( operators op, number *n1, number *n2 )
{
   integer *s1 ;
   single_float *s2 ;
   double_float *s3 ;
   long   x1 ;
   float  x2 ;
   double x3 ;

   long   y1 ;
   float  y2 ;
   double y3 ;
   coercion coerce ;
   coerce = to_int ;

   if ( strcmp(n1->GetName(), "<integer>" ) == 0)
   {
      n1->Getter(&x1) ;
   }
   else if ( strcmp(n1->GetName(), "<single-float>" ) == 0)
   {
      n1->Getter(&x2) ;
      coerce = to_float ;
   }
   else
   {
      n1->Getter(&x3) ;
      coerce = to_double ;
   }

   if ( strcmp(n2->GetName(), "<integer>" ) == 0)
   {
      n2->Getter(&y1) ;
      if ( coerce == to_float ) y2 = (float) y1 ;
      if ( coerce == to_double) y3 = (double) y1 ;
   }
   else if ( strcmp(n2->GetName(), "<single-float>" ) == 0)
   {
      n2->Getter(&y2) ;
      if ( coerce == to_int ) 
      {
         x2 = (float) x1 ;
         coerce = to_float ;
      }
      if ( coerce == to_double) y3 = (double) y2 ;
   }
   else
   {
      n2->Getter(&y3) ;
      if ( coerce == to_float ) x3 = (double) x2 ;
      if ( coerce == to_int) x3 = (double) x1 ;
      coerce = to_double ;
   }
   switch( coerce )
   {
   case to_int :
        s1 = new integer ;
        switch (op)
        {
        case Add :
             s1->Setter(x1 + y1) ;
             break ;
        case Sub :
             s1->Setter(x1 - y1) ;
             break ;
        case Mul :
             s1->Setter(x1 * y1) ;
             break ;
        case Div :
             s1->Setter(x1 / y1) ;
             break ;
        default :
             break ;
        }
        return s1 ;
        break ;
   case to_float :
        s2 = new single_float ;
        switch (op)
        {
        case Add :
             s2->Setter(x2 + y2) ;
             break ;
        case Sub :
             s2->Setter(x2 - y2) ;
             break ;
        case Mul :
             s2->Setter(x2 * y2) ;
             break ;
        case Div :
             s2->Setter(x2 / y2) ;
             break ;
        default :
             break ;
        }
        return s2 ;
        break ;
   case to_double :
        s3 = new double_float ;
        switch (op)
        {
        case Add :
             s3->Setter(x3 + y3) ;
             break ;
        case Sub :
             s3->Setter(x3 - y3) ;
             break ;
        case Mul :
             s3->Setter(x3 * y3) ;
             break ;
        case Div :
             s3->Setter(x3 / y3) ;
             break ;
        default :
             break ;
        }
        return s3 ;
        break ;
   }
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : compare
 | INPUT     : operators : test operatoren
 |             number    : een getal
 |             number    : een getal
 | OUTPUT    : -
 | RETURN    : een boolean object
 | DATE      :
 |
 | ABSTRACT  : Vergelijkingen tussen getallen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
static DylanObject *compare( compare_operators op, number *n1, number *n2 )
{
   boolean_type *s1 ;
   long   x1 ;
   float  x2 ;
   double x3 ;

   long   y1 ;
   float  y2 ;
   double y3 ;

   if ( strcmp(n1->GetName(), "<integer>" ) == 0)
   {
      n1->Getter(&x1) ;
      x3 = (double) x1 ;
   }
   else if ( strcmp(n1->GetName(), "<single-float>" ) == 0)
   {
      n1->Getter(&x2) ;
      x3 = (double) x2 ;
   }
   else
   {
      n1->Getter(&x3) ;
   }

   if ( strcmp(n2->GetName(), "<integer>" ) == 0)
   {
      n2->Getter(&y1) ;
      y3 = (double) y1 ;
   }
   else if ( strcmp(n2->GetName(), "<single-float>" ) == 0)
   {
       n2->Getter(&y2) ;
       y3 = (double) y2 ;
   }
   else
   {
      n2->Getter(&y3) ;
   }

   s1 = new boolean_type ;
   switch (op)
   {
      case Eq :
           s1->Setter(x3 == y3) ;
           break ;
      case Lt :
           s1->Setter(x3 < y3) ;
           break ;
      case Le :
           s1->Setter(x3 <= y3) ;
           break ;
      case Ne :
           s1->Setter(x3 != y3) ;
           break ;
      case Gt :
           s1->Setter(x3 > y3) ;
           break ;
      case Ge :
           s1->Setter(x3 >= y3) ;
           break ;
      default :
           break ;
    }
    return s1 ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_add
 | INPUT     : number : getal
 |             number : getal 
 | OUTPUT    : -
 | RETURN    : een som van 2 getallen
 | DATE      :
 |
 | ABSTRACT  : Optellen van 2 getallen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *number_add( number *n1, number *n2 )
{
   return ( arithmetic ( Add, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_sub
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    : -
 | RETURN    : een getal
 | DATE      :
 |
 | ABSTRACT  : aftrekken van 2 getallen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *number_sub( number *n1, number *n2 )
{
   return ( arithmetic ( Sub, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_mul
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    : -
 | RETURN    : een getal
 | DATE      :
 |
 | ABSTRACT  : Produkt van 2 getallen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *number_mul( number *n1, number *n2 )
{
   return ( arithmetic ( Mul, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_div
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    : -
 | RETURN    : een getal
 | DATE      :
 |
 | ABSTRACT  : Deling van 2 getallen
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *number_div( number *n1, number *n2 )
{
   return ( arithmetic ( Div, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_eq
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 = n2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *number_eq( number *n1, number *n2 )
{
   return ( compare ( Eq, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_ne
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 != n2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *number_ne( number *n1, number *n2 )
{
   return ( compare ( Ne, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_lt
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 < n2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *number_lt( number *n1, number *n2 )
{
   return ( compare ( Lt, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_gt
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 > n2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *number_gt( number *n1, number *n2 )
{
   return ( compare ( Gt, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_ge
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 >= n2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *number_ge( number *n1, number *n2 )
{
   return ( compare ( Ge, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_le
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 <= n2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *number_le( number *n1, number *n2 )
{
   return ( compare ( Le, n1, n2) ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : identity 
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    :
 | RETURN    : boolean object
 | DATE      :
 |
 | ABSTRACT  : n1 == n2 ? (niet geimplementeerd)
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *identity( DylanObject *n1, DylanObject *n2 )
{
   return NULL ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : number_sqrt
 | INPUT     : number : een getal
 | OUTPUT    : -
 | RETURN    : een getal
 | DATE      :
 |
 | ABSTRACT  : Berekenen van de vierkantswortel van een getal
 |             Output is steeds een double float object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *number_sqrt( number *n1 )
{
   long x1 ;
   float x2 ;
   double x3 ;

   static double_float s3 ;

   if ( strcmp(n1->GetName(), "<integer>" ) == 0)
   {
      n1->Getter(&x1) ;
      x3 = (double) x1 ;
   }
   else if ( strcmp(n1->GetName(), "<single-float>" ) == 0)
   {
      n1->Getter(&x2) ;
      x3 = (double) x2 ;
   }
   else
   {
      n1->Getter(&x3) ;
   }

   s3.Setter( sqrt(x3) ) ;

   return &s3 ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : local_random
 | INPUT     : integer : getal
 | OUTPUT    : -
 | RETURN    : een random getal (tussen 0 en n1)
 | DATE      :
 |
 | ABSTRACT  : Interface tussen de C library random call en Dylan
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *local_random( integer *n1 )
{
   long i ;
   n1->Getter(&i) ;
   srandom((unsigned int)i) ;
   return new integer( random() ) ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : number_atan2
 | INPUT     : number : een getal
 |             number : een getal
 | OUTPUT    : -
 | RETURN    : een double_float
 | DATE      :
 |
 | ABSTRACT  : Berekening van de arctangens (just an example)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *number_atan2( number *n1, number *n2 )
{
   long x1 ;
   float x2 ;
   double x3 ;
   long y1 ;
   float y2 ;
   double y3 ;

   double_float *s3 ;

   s3 = new double_float ;

   if ( strcmp(n1->GetName(), "<integer>" ) == 0)
   {
      n1->Getter(&x1) ;
      x3 = (double) x1 ;
   }
   else if ( strcmp(n1->GetName(), "<single-float>" ) == 0)
   {
      n1->Getter(&x2) ;
      x3 = (double) x2 ;
   }
   else
   {
      n1->Getter(&x3) ;
   }

   if ( strcmp(n2->GetName(), "<integer>" ) == 0)
   {
      n2->Getter(&y1) ;
      y3 = (double) y1 ;
   }
   else if ( strcmp(n2->GetName(), "<single-float>" ) == 0)
   {
      n2->Getter(&y2) ;
      y3 = (double) y2 ;
   }
   else
   {
      n1->Getter(&y3) ;
   }
   s3->Setter( atan2(x3,y3) ) ;

   return s3 ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : myand
 | INPUT     : boolean : een boolean waarde
 |             boolean : een boolean waarde
 | OUTPUT    : -
 | RETURN    : een boolean
 | DATE      :
 |
 | ABSTRACT  : logische and tussen 2 boolese waarden
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *myand( boolean_type *n1, boolean_type *n2 )
{
   boolean_type *s1 ;
   int x ;
   int y ;

   s1 = new boolean_type ;
   n1->Getter(&x) ;
   n2->Getter(&y) ;
   s1->Setter( x && y ) ;
   return s1 ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : myor
 | INPUT     : boolean : een boolean
 |             boolean : een boolean
 | OUTPUT    :
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Logische or tussen 2 boolese waarden
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *myor( boolean_type *n1, boolean_type *n2 )
{
   boolean_type *s1 ;
   int x ;
   int y ;

   s1 = new boolean_type ;
   n1->Getter(&x) ;
   n2->Getter(&y) ;
   s1->Setter( x || y ) ;
   return s1 ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : dylan_print
 | INPUT     : DylanObject : een object
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Afdrukken van een object
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *dylan_print( DylanObject *n1 )
{
   long x1 ;
   float x2 ;
   double x3 ;
   int b ;
   char  *str ;
   if ( strcmp(n1->GetName(), "<integer>" ) == 0)
   {
      n1->Getter(&x1) ;
      printf( "%ld\n", x1 ) ;
   }
   else if ( strcmp(n1->GetName(), "<single-float>" ) == 0)
   {
      n1->Getter(&x2) ;
      printf( "%f\n", x2 ) ;
   }
   else if ( strcmp(n1->GetName(), "<double-float>" ) == 0)
   {
      n1->Getter(&x3) ;
      printf( "%lf\n", x3 ) ;
   }
   else if ( strcmp(n1->GetName(), "<symbol>" ) == 0)
   {
      str = new char[255] ;
      n1->Getter(str) ;
      printf( "%s\n", str ) ;
      delete str ;
   }
   else if ( strcmp(n1->GetName(), "<string>" ) == 0)
   {
      str = new char[255] ;
      n1->Getter(str) ;
      if ( str[0] == '"' ) str = (str + 1) ;
      if ( str[strlen(str) - 1] == '"' ) str[strlen(str) - 1] = '\0' ;
      printf( "%s\n", str ) ;
      delete str ;
   }
   else if ( strcmp(n1->GetName(), "<boolean>" ) == 0)
   {
      n1->Getter(&b) ;
      if ( b) 
      {
         printf("#t") ;
      }
      else
      {
         printf("#f") ;
      }
   }
   else
   {
      n1->Print(0) ;
   }

   return object_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : make
 | INPUT     : DylanObject : een klasse
 | OUTPUT    : -
 | RETURN    : een instance van die klasse
 | DATE      :
 |
 | ABSTRACT  : instantieren van een bepaalde klasse (zonder
 |             initialisatie keywords)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *make( DylanObject *n1 )
{
   static DylanObject *o ;
   char  *str ;

   if ( strcmp(n1->GetName(), "<symbol>" ) == 0)
   {
      str = new char[255] ;
      n1->Getter(str) ;
      if ( ClassDict.SearchClass( str ) )
      {
         delete str ;
         if ( ClassDict.GetClass()->IsAbstract() )
         {
            error("You cannot make an instance of an abstract class") ;
         }
         o = ClassDict.GetClass()->Instance ( ClassDict.GetClass(), NULL ) ;
         return o ;
      }
   }
   return object_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : make2
 | INPUT     : DylanObject : een klasse
 |             list        : lijst van initialisatie keywords
 | OUTPUT    : -
 | RETURN    : een instance van die klasse
 | DATE      :
 |
 | ABSTRACT  : instantieren van een bepaalde klasse  met bepaalde
 |             initialisatie keywords ( deze keywords hangen af van
 |             de klasse ).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *make2( DylanObject *n1, list *n2 )
{
   static DylanObject *o ;
   static List<DylanObject *> *MyList ;
   char  *str ;

   if ( strcmp(n1->GetName(), "<symbol>" ) == 0)
   {
      str = new char[255] ;
      n1->Getter(str) ;
      MyList = new List<DylanObject *> ;
      n2->Getter( MyList ) ;
      if ( ClassDict.SearchClass( str ) )
      {
         delete str ;
         if ( ClassDict.GetClass()->IsAbstract() )
         {
            error("You cannot make an instance of an abstract class") ;
         }
         o = ClassDict.GetClass()->Instance ( ClassDict.GetClass(), MyList ) ;
         return o ;
      }
   }
   return object_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : myinstance
 | INPUT     : DylanObject : een bepaald object
 |             DylanObject : een type
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Testen of dat een bepaald object (n1) van het
 |             type (n2) is. Het gaat hem hier wel of een direct
 |             type (dus geen subklasse).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *myinstance( DylanObject *n1, DylanObject *n2 )
{
   char s[255] ;
   static boolean_type *result ;

   if ( strcmp( n2->GetName() , "<symbol>" ) != 0 )
   {
      printf( "Error : argument 2 is not a type\n" ) ;
      result = new boolean_type(0) ;
      return result;
   }
   n2->Getter(s) ;
   if ( strcmp(n1->GetName(), s) == 0)
   {
       result = new boolean_type(1) ;
       return result ;
   }
   result = new boolean_type(0) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : size
 | INPUT     : collection : een collectie (lijst, vector, ...)
 | OUTPUT    : -
 | RETURN    : integer object
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de lengte van een collectie
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *size( collection *n1 )
{
   static integer *result ;
   result = new integer(n1->Size()) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : empty
 | INPUT     : collection : een collectie
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Teruggeven of een bepaalde collectie leeg is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *empty( collection *n1 )
{
   static boolean_type *result ;
   result = new boolean_type(n1->Empty()) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : class_for_copy
 | INPUT     : mutable_sequence 
 | OUTPUT    : -
 | RETURN    : class naam van de mutable_sequence
 | DATE      :
 |
 | ABSTRACT  : teruggeven van de naam van de klasse van de 
 |             sequence.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *class_for_copy( mutable_sequence *n1 )
{
   static symbol *result ;
   result = new symbol(n1->GetName()) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : slot_initialized
 | INPUT     : DylanObject : instance van een klasse
 |             symbol      : naam van een slot
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Testen of een bepaald slot van een instance van een
 |             klasse wel geinitialiseerd is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *slot_initialized( DylanObject *n1, symbol *n2 )
{
   char s[255] ;
   static boolean_type *result ;
   n2->Getter(s) ;
   if ( n1->ReturnSlot(s) != NULL )
   {
      if ( n1->ReturnSlot( s )->GetValue() != NULL )
      {
         result = new boolean_type(1) ;
      }
      else
      {
         result = new boolean_type(0) ;
      }
   }
   else result = new boolean_type(0) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : sub_type
 | INPUT     : DylanObject : een object
 |             DylanObject : een object
 | OUTPUT    :
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Testen of dat een bepaald object n2 een subklasse
 |             is van object n1.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *sub_type( DylanObject *n1, DylanObject *n2 )
{
   DylanObject **Classes ;
   int i ;
   int Size ;
   char str1[255] ;
   char str2[255] ;

   static boolean_type *result ;
   if ( strcmp( n1->GetName() , "<symbol>" ) != 0 )
   {
      printf( "Error : argument 1 is not a type\n" ) ;
      result = new boolean_type(0) ;
      return result;
   }
   if ( strcmp( n2->GetName() , "<symbol>" ) != 0 )
   {
      printf( "Error : argument 2 is not a type\n" ) ;
      result = new boolean_type(0) ;
      return result;
   }
   n1->Getter(str1) ;
   n2->Getter(str2) ;

   result = new boolean_type(0) ;

   if ( ClassDict.SearchClass(str1) == 0 )  
   {
      printf ( "Unknown type : %s \n", str1 ) ;
   }

   Classes = ClassDict.GetClass()->GetSuperclass(&Size) ;
   for( i = Size - 1; i >= 0; i-- )
   {
      if ( strcmp ( Classes[i]->GetName(), str2) == 0 )
      {
         result = new boolean_type(1) ;
         break ;
      }
   } 

   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : object_class
 | INPUT     : DylanObject : een object
 | OUTPUT    : -
 | RETURN    : de klasse van het object
 | DATE      :
 |
 | ABSTRACT  : Ophalen van het type van een bepaald object.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *object_class( DylanObject *n1 )
{
   static symbol *result ;
   result = new symbol(n1->GetName()) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : odd
 | INPUT     : integer : een integer waarde
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Testen of dat een bepaalde integer oneven is
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *odd( integer *n1 )
{
   long anumber ;
   static boolean_type *result ;
   n1->Getter(&anumber) ;
   if ( 2 * ( anumber / 2 ) == anumber )
   {
      result = new boolean_type(0) ;
   }
   else
   {
      result = new boolean_type(1) ;
   }
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : even
 | INPUT     : integer : een getal (integer)
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Test of een bepaald getal even is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *even( integer *n1 )
{
   long anumber ;
   static boolean_type *result ;
   n1->Getter(&anumber) ;
   if ( 2 * ( anumber / 2 ) == anumber )
   {
      result = new boolean_type(1) ;
   }
   else
   {
      result = new boolean_type(0) ;
   }
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : zero
 | INPUT     : real : een reeel getal
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : test of een bepaald reeel getal 0 is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *zero( real *n1 )
{
   double anumber ;
   static boolean_type *result ;
   n1->Getter(&anumber) ;
   if ( anumber  == 0 )
   {
      result = new boolean_type(1) ;
   }
   else
   {
      result = new boolean_type(0) ;
   }
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : positive
 | INPUT     : real : een reeel getal
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : test of een getal > 0 is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *positive( real *n1 )
{
   double anumber ;
   static boolean_type *result ;
   n1->Getter(&anumber) ;
   if ( anumber  > 0 )
   {
      result = new boolean_type(1) ;
   }
   else
   {
      result = new boolean_type(0) ;
   }
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : negative
 | INPUT     : real : reeel getal
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : test of een bepaald getal < 0 is.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *negative( real *n1 )
{
   double anumber ;
   static boolean_type *result ;
   n1->Getter(&anumber) ;
   if ( anumber  < 0 )
   {
      result = new boolean_type(1) ;
   }
   else
   {
      result = new boolean_type(0) ;
   }
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : make_list
 | INPUT     : rest_list : sequentie van objecten
 | OUTPUT    : -
 | RETURN    : een lijst
 | DATE      :
 |
 | ABSTRACT  : implementatie van de functie 
 |             list(1,2,3,4) ----> #(1,2,3,4)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *make_list( rest_list *n1 )
{
   return n1 ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : values
 | INPUT     : rest_list : een sequenctie van objecten
 | OUTPUT    : -
 | RETURN    : values_list
 | DATE      :
 |
 | ABSTRACT  : Deze functie dient om bepaalde methoden toe te laten
 |             om multiple values terug te geven.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *values( rest_list *n1 )
{
   static values_list *result ;
   static List<DylanObject *> *l ;

   l = new List<DylanObject *> ;
   n1->Getter(l) ;
   result = new values_list(l) ;

   return result ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : string_eq
 | INPUT     : string : een string
 |             string : een string
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : Test of 2 strings gelijk zijn
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *string_eq( string *n1, string *n2 )
{
   static boolean_type *result ;
   char s1[255] ;
   char s2[255] ;
   
   n1->Getter(s1) ;
   n2->Getter(s2) ;  
   result = new boolean_type( strcmp(s1,s2) == 0) ;
   return ( result ) ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : symbol_eq
 | INPUT     : symbol : een symbool
 |             symbol : een symbool
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : test of 2 dylan symbolen gelijk zijn (intern zijn 
 |             symbolen gewoon strings).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *symbol_eq( symbol *n1, symbol *n2 )
{
   static boolean_type *result ;
   char s1[255] ;
   char s2[255] ;
   
   n1->Getter(s1) ;
   n2->Getter(s2) ;  
   result = new boolean_type( strcmp(s1,s2) == 0) ;
   return ( result ) ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : string_gt
 | INPUT     : string  : een string
 |             string  : een string
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : string1 > string2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *string_gt( string *n1, string *n2 )
{
   static boolean_type *result ;
   char s1[255] ;
   char s2[255] ;
   
   n1->Getter(s1) ;
   n2->Getter(s2) ;  
   result = new boolean_type( strcmp(s1,s2) > 0) ;
   return ( result ) ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : string_lt
 | INPUT     : string : een string
 |             string : een string
 | OUTPUT    : -
 | RETURN    : boolean
 | DATE      :
 |
 | ABSTRACT  : string1 < string2 ?
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *string_lt( string *n1, string *n2 )
{
   static boolean_type *result ;
   char s1[255] ;
   char s2[255] ;
   
   n1->Getter(s1) ;
   n2->Getter(s2) ;  
   result = new boolean_type( strcmp(s1,s2) < 0) ;
   return ( result ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : write
 | INPUT     : rest_list : een sequenctie van objecten
 | OUTPUT    : -
 | RETURN    : altijd #f
 | DATE      :
 |
 | ABSTRACT  : Uitschrijven van een sequentie van objecten
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *write( rest_list *n1 )
{
   static List<DylanObject *> *l ;
   int i ;

   l = new List<DylanObject *> ;
   n1->Getter(l) ;

   for( i = 1; i <= l->GetSize(); i++ )
   {
       l->MoveTo(i) ;
       l->GetItem()->Print(0) ;
   }
   printf( "\n") ;
   return false_object ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : myfloor
 | INPUT     : real : reeel getal
 | OUTPUT    : -
 | RETURN    : integer
 | DATE      :
 |
 | ABSTRACT  : resultaat : floor( reeel getal ), afronden naar 
 |             beneden.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *myfloor( real *n1 )
{
   double l ;
   static integer *result ;
   n1->Getter(&l) ;
   result = new integer( (long) floor(l) ) ;
   return result ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : myceil
 | INPUT     : real : een reeel getal
 | OUTPUT    : -
 | RETURN    : integer
 | DATE      :
 |
 | ABSTRACT  : afronden van een reeel getal naar boven.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *myceil( real *n1 )
{
   double l ;
   static integer *result ;
   n1->Getter(&l) ;
   result = new integer( (long) ceil(l) ) ;
   return result ;
}
/*
 +------------------------------------------------------------------
 | FUNCTION  : myround
 | INPUT     : real : een reeel getal
 | OUTPUT    : -
 | RETURN    : integer
 | DATE      :
 |
 | ABSTRACT  : afronden van een getal (met de standaard afrondings-
 |             regels).
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *myround( real *n1 )
{
   double l ;
   static integer *result ;
   n1->Getter(&l) ;
   result = new integer( (long) rint(l) ) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : as_uppercase
 | INPUT     : character : een character
 | OUTPUT    : -
 | RETURN    : character
 | DATE      :
 |
 | ABSTRACT  : Omzetten van een lowercase character naar een 
 |             uppercase character.
 |             Opgelet de gebruikte karakterset is ASCII 
 |             (volgens de standaard zal dit unicode moeten worden)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *as_uppercase( character *n1 )
{
   static character *result ;
   char x ;
   n1->Getter(&x) ;
   if ( x > 96 && x < 123 ) x -= 32 ;
   result = new character( x ) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : as_lowercase
 | INPUT     : character : een character
 | OUTPUT    : -
 | RETURN    : character
 | DATE      :
 |
 | ABSTRACT  : Omzetten van een uppercase character naar een 
 |             lowercase character.
 |             Opgelet de gebruikte karakterset is ASCII 
 |             (volgens de standaard zal dit unicode moeten worden)
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
DylanObject *as_lowercase( character *n1 )
{
   static character *result ;
   char x ;
   n1->Getter(&x) ;
   if ( x < 96 && x > 64 ) x += 32 ;

   result = new character( x ) ;
   return result ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : local_apply
 | INPUT     : function : een methode
 |             list     : een lijst van argumenten
 | OUTPUT    : -
 | RETURN    : een object
 | DATE      :
 |
 | ABSTRACT  : Uitvoeren van de functie f over een lijst van
 |             argumenten
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *local_apply( function *f, list *lijst )
{
   DylanObject *Arg[255] ; // 255 argumenten lijkt mij een voldoende limitatie
   List<DylanObject *> *P ;

   int i ;
   P = new List<DylanObject *> ;

   for( i = 0; i < lijst->Size(); i++ )
   {
      Arg[i+1] = lijst->GetElement(i) ;
      P->AppendItem(lijst->GetElement(i) ) ;
   }
   return apply( f, f->GetEnv(),P,Arg,NULL ) ; 
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : MakeMethod
 | INPUT     : const char * : naam van de methode (Dylan syntax)
 |             PRIM   : primitive (C naam)
 |             ...    : variabel aantal argumenten
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Toevoegen van een primitive methode aan de 
 |             methode dictionnary.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void MakeMethod( const char *MethodName, PRIM g , DylanObject *obj, ...)  
{
   List<Parameter *> *ParList ;
   va_list            args ;
   DylanObject       *AnObject ;
   Method            *Primitive ;
   int                Counter = 0 ;

   ParList = new List<Parameter *> ;
   ParList->AppendItem( new Parameter( (parameter_types) obj->ReturnParaType(), "dummy", new ConstRef(obj), (char *) NULL )) ;

   va_start( args, obj ) ;
   AnObject = va_arg( args, DylanObject * ) ;
   while ( AnObject != NULL )
   {
      ParList->AppendItem( new Parameter( (parameter_types) AnObject->ReturnParaType(), "dummy", new ConstRef(AnObject), (char *) NULL )) ;
      AnObject = va_arg( args, DylanObject * ) ;
   }

   Primitive = new Method( MethodName, ParList, g ) ;
   MethodDict.InsertMethod( Primitive, 0 ) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : install_primitives
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Installeren van de primitiven in de methode 
 |             dictionnary.
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void install_primitives()
{
   MakeMethod( "+", (PRIM)number_add, number_object, number_object, NULL ) ;
   MakeMethod( "-", (PRIM)number_sub, number_object, number_object, NULL ) ;
   MakeMethod( "*", (PRIM)number_mul, number_object, number_object, NULL ) ;
   MakeMethod( "/", (PRIM)number_div, number_object, number_object, NULL ) ;
   MakeMethod( "odd?", (PRIM)odd, integer_object, NULL ) ;
   MakeMethod( "even?", (PRIM)even, integer_object, NULL ) ;
   MakeMethod( "zero?", (PRIM)zero, real_object, NULL ) ;
   MakeMethod( "positive?", (PRIM)positive, real_object, NULL ) ;
   MakeMethod( "negative?", (PRIM)negative, real_object, NULL ) ;
   MakeMethod( "sqrt", (PRIM)number_sqrt, number_object, NULL ) ;
   MakeMethod( "atan2", (PRIM)number_atan2, number_object,number_object, NULL ) ;
   MakeMethod( "print", (PRIM)dylan_print, object_object, NULL ) ;
   MakeMethod( "=", (PRIM)string_eq, string_object,string_object, NULL ) ;
   MakeMethod( "=", (PRIM)symbol_eq, symbol_object,symbol_object, NULL ) ;
   MakeMethod( "=", (PRIM)number_eq, number_object,number_object, NULL ) ;
   MakeMethod( ">", (PRIM)string_gt, string_object,string_object, NULL ) ;
   MakeMethod( ">", (PRIM)number_gt, number_object,number_object, NULL ) ;
   MakeMethod( "<", (PRIM)number_lt, number_object,number_object, NULL ) ;
   MakeMethod( "<", (PRIM)string_lt, string_object,string_object, NULL ) ;
   MakeMethod( ">=", (PRIM)number_ge, number_object,number_object, NULL ) ;
   MakeMethod( "<=", (PRIM)number_le, number_object,number_object, NULL ) ;
   MakeMethod( "~=", (PRIM)number_ne, number_object,number_object, NULL ) ;
   MakeMethod( "==", (PRIM)identity, object_object,object_object, NULL ) ;
   MakeMethod( "|", (PRIM)myor, boolean_object,boolean_object, NULL ) ;
   MakeMethod( "&", (PRIM)myand, boolean_object,boolean_object, NULL ) ;
   MakeMethod( "make", (PRIM)make, symbol_object, NULL ) ;
   MakeMethod( "make", (PRIM)make2, symbol_object, rest_list_object, NULL ) ;
   MakeMethod( "instance?", (PRIM)myinstance, object_object, object_object, NULL ) ;
   MakeMethod( "slot-initialized?", (PRIM)slot_initialized, object_object, symbol_object,  NULL ) ;
   MakeMethod( "subtype?", (PRIM)sub_type, object_object, object_object,  NULL ) ;
   MakeMethod( "object-class", (PRIM)object_class, object_object,  NULL ) ;
   MakeMethod( "size", (PRIM)size, collection_object,  NULL ) ;
   MakeMethod( "empty?", (PRIM)empty, collection_object,  NULL ) ;
   MakeMethod( "class-for-copy", (PRIM)class_for_copy, mutable_sequence_object,  NULL ) ;
   MakeMethod( "list", (PRIM)make_list, rest_list_object,  NULL ) ;
   MakeMethod( "values", (PRIM)values, rest_list_object,  NULL ) ;
   MakeMethod( "write", (PRIM)write, rest_list_object,  NULL ) ;
   MakeMethod( "floor", (PRIM)myfloor, real_object,  NULL ) ;
   MakeMethod( "ceil", (PRIM)myceil, real_object,  NULL ) ;
   MakeMethod( "round", (PRIM)myround, real_object,  NULL ) ;
   MakeMethod( "as-uppercase", (PRIM)as_uppercase, character_object,  NULL ) ;
   MakeMethod( "as-lowercase", (PRIM)as_lowercase, character_object,  NULL ) ;
   MakeMethod( "%apply", (PRIM)local_apply, function_object, list_object,  NULL ) ;
   MakeMethod( "random", (PRIM)local_random, integer_object, NULL ) ;
}
