/*
 +------------------------------------------------------------------
 | FILENAME  : tokens.h
 | DATE      : 01/09/1994
 |
 | ABSTRACT  : token structuur, gebruikt door lex en yacc.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _TOKENS
#define _TOKENS
struct Token_Struct
     { int length ;
       int type ;
       int lineno ;
       char *name ;
     } Token_Struct ;
#endif
