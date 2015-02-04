/*
 +------------------------------------------------------------------
 | FILENAME  : types.h
 | DATE      : 01/09/1994
 |
 | ABSTRACT  : bevat een aantal types, nodig om het programma in
 |             gang te krijgen.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#include <gc/gc_cpp.h>

#ifndef _TYPES
#define _TYPES
#ifndef NULL
  #define NULL (void *) 0
#endif

class Expression ;
class Assignment ;
class Conditional ;
class AddSub ;
class MulDiv ;
class Pri ;
class Variable ;
class DylanClass ;
class ClassDictionnary ;
class DylanObject ;
class Body ;
class Method ;
class Environment ;

typedef char * StackElement ;
typedef int    Boolean ;
typedef float  Real ;
typedef char   Character ;
typedef int    Integer ;
typedef char * String ;
typedef DylanObject *(*PRIM)(...) ;
#ifndef FALSE
const   int  FALSE = 0 ;
const   int  TRUE  = 1 ;
#endif

enum parameter_types { normal,  
                       next_par, 
                       rest_par, 
                       key_par, 
                       all_keys_par,
                       singleton } ;

extern void strrpt( char *s, char c, int cnt ) ;
extern void error(const char *s) ;

extern DylanObject *object_object ;
extern DylanObject *symbol_object ;
extern DylanObject *string_object ;
extern DylanObject *character_object;
extern DylanObject *type_object     ;
extern DylanObject *boolean_object  ;
extern DylanObject *number_object   ;
extern DylanObject *real_object     ;
extern DylanObject *rational_object ;
extern DylanObject *integer_object  ;
extern DylanObject *float_object    ;
extern DylanObject *s_float_object  ;
extern DylanObject *d_float_object  ;
extern DylanObject *e_float_object  ;
extern DylanObject *function_object ;
extern DylanObject *true_object  ;
extern DylanObject *false_object ;
extern DylanObject *list_object ;
extern DylanObject *vector_object ;
extern DylanObject *array_object  ;
extern DylanObject *range_object  ;
extern DylanObject *sequence_object ;
extern DylanObject *mutable_sequence_object;
extern DylanObject *collection_object ;
extern DylanObject *rest_list_object ;
extern DylanObject *class_object ;

extern Environment *the_global_environment ;

extern int TheDylanScope ;
#endif
