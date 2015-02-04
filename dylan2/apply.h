#ifndef _APPLY
#define _APPLY
#include "object.h"
#include "expression.h"
#include "method.h"
#include "environment.h"
extern DylanObject *apply( DylanObject *operand, 
                    Environment *Env,
                    List<DylanObject *> *P,
                    DylanObject **Arg,
                    List<Argument *> *Arguments ) ;
#endif
