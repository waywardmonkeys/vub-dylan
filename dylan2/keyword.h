#ifndef __KEYWORD
#define __KEYWORD
#include "object.h"

class keyword : public DylanObject 
{
    private :
        char *name ;
        DylanObject *value ;
    public:
        /* constructors */
        keyword() ;
        keyword( char *s, DylanObject *o)  ;


        int operator== (const DylanObject *X) ;
        DylanObject *GetValue(Environment *) ;
        void         Getter(char *s) ;
        void         Print(int *i) ;
} ;
#endif
