#ifndef __KEYWORD
#define __KEYWORD
#include "object.h"

class keyword : public DylanObject 
{
    private :
        const char *name ;
        DylanObject *value ;
    public:
        /* constructors */
        keyword() ;
        keyword( const char *s, DylanObject *o)  ;


        int operator== (const DylanObject *X) ;
        DylanObject *GetValue(Environment *) ;
        void         Getter(char *s) ;
        void         Print(int *i) ;
} ;
#endif
