#include "keyword.h"

/*
 +------------------------------------------------------------------
 | FUNCTION  : keyword::keyword
 | INPUT     : -
 | OUTPUT    : -
 | RETURN    : een keyword object
 | DATE      :
 |
 | ABSTRACT  : Constructor van keyword objecten
 |             keyword objecten zijn objecten met label
 |             bvb x: 100 of y: 3.1415
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
keyword::keyword()
{ 
   id = "<keyword>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : keyword::keyword
 | INPUT     : char        : naam van het keyword
 |             DylanObject : waarde van het keyword
 | OUTPUT    : -
 | RETURN    : een keyword
 | DATE      :
 |
 | ABSTRACT  : Constructor van een keyword met default waarden
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
keyword::keyword( char *s, DylanObject *o)
{ 
   name = s ;
   value = o ;
   id = "<keyword>"; 
   Abstract = FALSE ; 
   Sealed = TRUE; 
   Instantiable = TRUE ; 
   NbrSuperclasses = 1 ;
   Superclass = new (GC) DylanObject * [1] ;
   Superclass[0] = new DylanObject ;
}


/*
 +------------------------------------------------------------------
 | FUNCTION  : keyword::GetValue
 | INPUT     : Environment : een omgeving
 | OUTPUT    : -
 | RETURN    : De waarde van een keyword
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de waarde van een keyword
 |             (omgeving waarin het keyword zit wordt niet gebruikt)
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
DylanObject *keyword::GetValue(Environment *Env)
{ 
   return value ;
} 

/*
 +------------------------------------------------------------------
 | FUNCTION  : keyword::Getter
 | INPUT     : -
 | OUTPUT    : char *
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Ophalen van de naam van het keyword
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void keyword::Getter(char *s) 
{ 
   strcpy(s,name) ;
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : keyword::Print
 | INPUT     : int  : indentatie
 | OUTPUT    : -
 | RETURN    : -
 | DATE      :
 |
 | ABSTRACT  : Pretty printer van een keyword
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
void keyword::Print(int *i) 
{ 
   printf( "%s ", name ) ; 
   value->Print(i);
}

/*
 +------------------------------------------------------------------
 | FUNCTION  : keyword::operator==
 | INPUT     : DylanObject : een dylan object
 | OUTPUT    : -
 | RETURN    : TRUE   : namen gelijk
 |             FALSE  : namen niet gelijk
 | DATE      :
 |
 | ABSTRACT  : Met deze operator testen we of de NAMEN van de keywords
 |             gelijk zijn.
 |             De waarden van de keywords worden met andere operatoren
 |             getest
 |
 | CHANGES   :
 +------------------------------------------------------------------
 */
int keyword::operator==( const DylanObject *X )
{
   return( strcmp(this->name , ((keyword *) X)->name ) == 0) ;
}
