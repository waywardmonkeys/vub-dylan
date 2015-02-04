/*
 +------------------------------------------------------------------
 | FILENAME  : primitive.h
 | DATE      :
 |
 | ABSTRACT  : enkele dylan primitieven.
 |             Sommige standaard dylan functies zijn in C 
 |             geimplementeerd uit performance overwegingen
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _PRIMITIVE
#define _PRIMITIVE
#include "object.h"
#include "class.h"
#include "integer.h"
#include "double_float.h"
#include "single_float.h"
#include "extended_float.h"
#include "boolean.h"
#include "function.h"
#include "symbol.h"
#include "rest_list.h"
#include "values_list.h"
#include "range.h"
#include "array.h"
#include "vector.h"
#include "list_type.h"
#include "string.h"
#include "character.h"
#include "variable.h"

extern void install_primitives() ;
extern ClassDictionnary ClassDict ;

#endif
