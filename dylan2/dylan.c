/*
 +------------------------------------------------------------------
 | FILENAME  : dylan.c
 | DATE      : 01/09/1994
 |
 | ABSTRACT  : Driver programma voor de Dylan compiler
 |             volgende opties zijn beschikbaar :
 |             -g : toon debug info.
 |             -p : pretty print (moet nog wat bijgeschaafd worden)
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#define YYDEBUG 9
#include <stdio.h>
#include "object.h"
#include "boolean.h"
#include "number.h"
#include "real.h"
#include "symbol.h"
#include "character.h"
#include "rational.h"
#include "integer.h"
#include "float.h"
#include "single_float.h"
#include "double_float.h"
#include "extended_float.h"
#include "function.h"
#include "vector.h"
#include "range.h"
#include "list_type.h"
#include "collection.h"
#include "sequence.h"
#include "mutable_sequence.h"
#include "array.h"
#include "type.h"
#include "rest_list.h"
#include "string.h"
#include "class_type.h"
#include "environment.h"
// creatie van een aantal standaard objecten

DylanObject *object_object           = new DylanObject ;
DylanObject *symbol_object           = new symbol ;
DylanObject *string_object           = new string  ;
DylanObject *character_object        = new character ;
DylanObject *type_object             = new type ;
DylanObject *class_object            = new class_type ;
DylanObject *boolean_object          = new boolean_type ;
DylanObject *number_object           = new number ;
DylanObject *real_object             = new real ;
DylanObject *rational_object         = new rational ;
DylanObject *integer_object          = new integer ;
DylanObject *float_object            = new myfloat ;
DylanObject *s_float_object          = new single_float ;
DylanObject *d_float_object          = new double_float ;
DylanObject *e_float_object          = new extended_float ;
DylanObject *function_object         = new function ;
DylanObject *true_object             = new boolean_type(1) ;
DylanObject *false_object            = new boolean_type(0) ;
DylanObject *list_object             = new list ;
DylanObject *vector_object           = new vector ;
DylanObject *array_object            = new array ;
DylanObject *range_object            = new range ;
DylanObject *sequence_object         = new sequence ;
DylanObject *mutable_sequence_object = new mutable_sequence ;
DylanObject *collection_object       = new collection ;
DylanObject *rest_list_object        = new rest_list ;
Environment *the_global_environment  = new Environment ;

#include "y.tab.c"
int yywrap()
{
   return 1 ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : error
 | INPUT     : errorstring
 | OUTPUT    : -
 | RETURN    : -
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Tonen van een errorstring en stoppen 
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void error( char *s )
{
   fprintf( stderr, "error : %s\n", s ) ;
   exit(-1) ;
}

main(int argc, char *argv[])
{
  int i = 0 ;
  DylanObject *Result ;
  char filename[255] ;
  Boolean prettyprint ;
  Boolean dump ;
  char command[255] ;

  if ( argc < 2 )
  {
     error( "usage : dylan <filename> " ) ;
  } 
  switch ( argc )
  {
  case 2: strcpy( filename, argv[1] ) ;
          break ;
  case 3: if ( strcmp(argv[1] ,"-p") == 0 ) prettyprint = TRUE ;
          if ( strcmp(argv[1] ,"-g") == 0 ) dump = TRUE ;
          strcpy( filename, argv[2]) ;
          break ;
  case 4: if ( strcmp(argv[1] ,"-p") == 0 ) prettyprint = TRUE ;
          if ( strcmp(argv[1] ,"-g") == 0 ) dump = TRUE ;
          if ( strcmp(argv[2] ,"-p") == 0 ) prettyprint = TRUE ;
          if ( strcmp(argv[2] ,"-g") == 0 ) dump = TRUE ;
          strcpy( filename, argv[3]) ;
          break ;
  default: break ;
  } ;
  install_primitives() ;
  MyProgram = new Body ;
  sprintf( command, "/bin/sh -c 'cat init.dyl %s > .tmp'", filename );
  system(command) ;
/*  yyin = fopen( "init.dyl", "r" ) ;
  yyparse() ;
  fclose(yyin) ;*/

  yyin = fopen( ".tmp", "r" ) ;
  if ( yyin == NULL )
  {
      error( "Error occured during opening of file !" ) ;
  }

  yyparse();
  fclose(yyin) ;
  system( "rm .tmp" ) ;
  if ( dump )
  {
     VarDict.Dump() ;
     MethodDict.Dump() ;
  }
  if ( prettyprint )
  {
     printf( "\n\n-------------- AFDRUKKEN PROGRAMMA ------------\n" ) ;
     MyProgram->Print(&i) ;
  }

  TheDylanScope = -1 ;

  Result = MyProgram->GetValue(the_global_environment) ;
  if ( Result != NULL ) 
  {
     Result->Print(0) ;
  }
  else
  {
     printf( "#f\n") ;
  }
  printf( "\n\n=============== EINDE ======================\n" ) ;

}
