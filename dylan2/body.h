
/*
 +------------------------------------------------------------------
 | FILENAME  : body.h
 | DATE      : 01/10/1994
 |
 | ABSTRACT  : Body is een lijst van constituenten, alnaargelang
 |             het soort constituent wordt een bepaalde actie
 |             uitgevoerd.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _BODY
#define _BODY

#include "const.h"

class Body : public gc
{
   private :
      struct BodyStruct
        { Constituent *C ;
          BodyStruct  *prev ;
          BodyStruct  *next ;
        } ;

      struct BodyStruct *AProgram ;
      struct BodyStruct *Top ;
   public :
      Body() { AProgram = new (GC) BodyStruct ; 
               AProgram->next = NULL ; 
               AProgram->prev = NULL ;
               Top = NULL ;
               }
      Body( const Body *B ) ;
      void Run() ;

      void AppendConstituent( Constituent *C )  ;
      void Print(int *)  ;
      DylanObject *GetValue(Environment *) ;
} ;
#endif
