/*
 +------------------------------------------------------------------
 | FILENAME  : property.h
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Elke klasse heeft een aantal properties, op moment
 |             van het parsen worden die in een lijst weggestopt.
 |             Deze lijst is tijdelijk want eenmaal dat een klasse
 |             geparsed is mogen die weg.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _PROPERTY
#define _PROPERTY
class Expression ;
struct Property
{
    char       *keyword ;
    Expression *value ;
    void Print(int *) {} ;
} ;
#endif /* _PROPERTY */
