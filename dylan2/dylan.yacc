/*
 +------------------------------------------------------------------
 | FILENAME  : dylan.yacc
 | DATE      : 01/09/1994
 |
 | ABSTRACT  : Bevat de grammatica van deze dylan implementatie.
 |             De parse tree wordt omgzet in een abstracte grammatica.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
%{
   /* declaration van lokale variabelen */
   #include <stdio.h>
   #include "tokens.h"
   #include "body.h"
   #include "property.h"
   #include "primitive.h"
   #include "statement.h"
   #include "method.h"
   #include "variable.h"
   #include "keyword.h"
   #include "class_type.h"
   Body *MyProgram ;
   Variable *ForParse ;
   Variable *Sentinel = new Variable( "________SENTINEL", TRUE ) ;
   symbol *Symbol ;
   Parameter *temp ;
   Variable  *tempvar ;
   int i = 0 ;
   int scope = 0 ;
   function *Function ; 
   ClassDictionnary ClassDict ;
   DataDictionnary  VarDict ;

   void yyerror(const char *);
   int yylex(void);

%}

%union { struct Token_Struct *token ;
	 struct tempvar *V;
	 Constituent  *C ;
	 Body *B; 
	 Variable *binding ;
	 class_type *D ;
	 List<DylanObject *> *SuperClasses ;
	 DylanObject *Object ;
	 List<Slot_specs *> *Slots ;
	 List<DylanObject *> *Constants ;
	 Property *Prop ;
	 List<Property *> *PropList ;
	 slot_allocation SlotAlloc ;
	 slot_adjectives SlotAdj ;
	 Slot_specs  *ASlot ;
         class_adjectives Flags ;
         DylanObject *literal ;
         Expression *Expr ;
         Expression *leaf ;
         CaseBody *case_body ;
         Bound    *bound ;
         Clause   *clause ;
         List<Clause *> *clauses ;
         For      *AFor ;
         Begin    *begin ;
         List<Expression *> *Expressions ;
         List<SelectElement *> *selectbody ;
         List<Variable *> *varlist ;
         List<Parameter *> *paramlist ;
         Method  *method ;
         Parameter *parameter ;
         Argument  *argument ;
         List<Argument *> *arguments ;
	 }
	 
%token <token> SYMBOL  
%token <token> MINUS  
%token <token> ADD  
%token <token> MUL  
%token <token> DIV  
%token <token> ASSIGN  
%token <token> NE  
%token <token> LT  
%token <token> GT  
%token <token> LE  
%token <token> GE  
%token <token> AND  
%token <token> OR  
%token <token> KEYWORD  
%token <token> STRING 
%token <token> TILDE 
%token <token> ABOVE 
%token <token> MYBEGIN 
%token <token> BELOW 
%token <token> BLOCK 
%token <token> BY 
%token <token> CASE 
%token <token> CLASS 
%token <token> CLEANUP 
%token <token> CONSTANT 
%token <token> DEFINE 
%token <token> ELSEIF
%token <token> ELSE
%token <token> END 
%token <token> EXCEPTION 
%token <token> FINALLY 
%token <token> FOR 
%token <token> FROM 
%token <token> GENERIC 
%token <token> HANDLER 
%token <token> IF 
%token <token> IN 
%token <token> INSTANCE 
%token <token> LET 
%token <token> LOCAL 
%token <token> METHOD 
%token <token> OTHERWISE 
%token <token> SELECT 
%token <token> SLOT 
%token <token> SUBCLASS 
%token <token> THEN 
%token <token> TO 
%token <token> UNLESS 
%token <token> UNTIL 
%token <token> VARIABLE 
%token <token> VIRTUAL 
%token <token> WHILE 
%token <token> INTEGER
%token <token> FLOAT
%token <token> RATIO
%token <token> LPAREN
%token <token> RPAREN
%token <token> COMMA
%token <token> PERIOD
%token <token> SEMICOLON
%token <token> LBRACKET
%token <token> RBRACKET
%token <token> LBRACE
%token <token> RBRACE
%token <token> COLON2
%token <token> EQUAL
%token <token> EQUAL2
%token <token> BIN_OP
%token <token> ARROW
%token <token> LIST_LIT
%token <token> VECTOR_LIT
%token <token> QMARK
%token <token> QMARK2
%token <token> DOTS3
%token <token> BTRUE
%token <token> BFALSE
%token <token> REST 
%token <token> NEXT
%token <token> KEY
%token <token> ALL_KEYS
%token <token> CHAR_LIT
%token <token> OPEN
%token <token> SEALED
%token <token> FREE
%token <token> ABSTRACT
%token <token> PRIMARY
%token <token> CONCRETE
%token <token> LIBRARY
%token <token> MODULE
%token <token> EXPORT_OPTION
%token <token> IMPORT_OPTION
%token <token> RENAME_OPTION
%token <token> EXCLUDE_OPTION
%token <token> PREFIX_OPTION
%token <token> USE
%token <token> EXPORT
%token <token> IMPORT
%token <token> RENAME
%token <token> ALL
%token <token> CREATE
%token <token> INHERITED

%type <V> variable
%type <D> class_definition 
%type <B> constituents body then_part else_part elseif_part body_label finally_opt
%type <C> constituent defining_form local_declaration
%type <method> generic_function_definition generic_function_body method_body method_definition anonymous_method local_methods
%type <bound> bound_opt
%type <clause> clause
%type <SuperClasses> superclasses
%type <Prop> property
%type <PropList> property_list property_list_opt 
%type <SlotAlloc> alloc_opt
%type <SlotAdj> slot_adj_opt
%type <token> symbol_opt 
%type <ASlot> slot_spec
%type <Slots> slot_specs slot_specs_opt
%type <Flags> flags
%type <literal> literal constant 
%type <Constants> constants constants_opt
%type <Expr> expression  binary_operand value statement case_label increment_opt default_opt type unary_operand
%type <Object> slot_type_opt
%type <leaf> leaf operand
%type <binding> bindings
%type <case_body> case_body
%type <AFor> for_body
%type <clauses> clauses
%type <Expressions> select_label 
%type <Expressions> expressions 
%type <selectbody> select_body
%type <varlist> variable_list variables variable_list_opt
%type <paramlist> parameter_list_opt parameters next_rest_key_parameter_list rest_key_parameter_list key_parameter_list keyword_parameters_opt
%type <parameter> parameter keyword_parameter
%type <argument> argument
%type <arguments> arguments arguments_opt
%right ASSIGN
%left MINUS ADD
%left DIV MUL
%left AND OR
%left GE LE LT EQUAL NE GT EQUAL2
%%
 
dylan_program : body  
                { MyProgram = $1 ; } 
              ;

body :  /* empty body */  
     { $$ = NULL ; }
     |  constituents semi_opt
        { $$ = $1 ; }
     ;

constituents : constituent 
               { $$ = new Body ; $$->AppendConstituent($1) ; }
               | constituents SEMICOLON constituent
               { $1->AppendConstituent($3) ;
                 $$ = $1 ;
                 delete $2 ;
               }
             ;

constituent : defining_form
              {  $1->SetLocal(FALSE) ;
                 $$ = $1 ; }
              | local_declaration
              { $1->SetLocal(TRUE) ;
                $$ = $1 ; } 
              | expression
              { $1->SetLocal(FALSE) ;
                $$ = $1 ; } ;
              
              ;

defining_form : DEFINE flags METHOD { scope++ ; } method_definition
              { $5->SetMethodAdj( (method_adjectives) $2) ; 
                delete $1 ; delete $3 ; 
                MethodDict.InsertMethod($5, 0) ;
                scope-- ; 
                VarDict.InsertVar( Sentinel, scope ) ;
                $$ = $5 ;
              }
              | DEFINE flags GENERIC {scope++ ; } generic_function_definition
              { $5->SetMethodAdj( (method_adjectives) $2) ;
                delete $1 ; delete $3 ;
                $$ = $5 ;
                scope-- ;
                VarDict.InsertVar( Sentinel, scope ) ;
              }
              | DEFINE flags CLASS class_definition
              { $4->SetClassAdj($2) ;
                delete $1 ; delete $3 ;
                $$ = new DylanClass($4) ;
                ClassDict.InsertClass( $4 ) ;
              }
              | DEFINE CONSTANT bindings
              {  $3->SetConstant() ;
                 $$ = $3 ;
                 VarDict.InsertVar($3,0) ;
                 delete $1;
                 delete $2; }
              | DEFINE VARIABLE bindings 
              {  $$ = $3 ;
                 VarDict.InsertVar($3,0) ;
                 delete $1;
                 delete $2; }
	      | DEFINE LIBRARY library_definition
	      { $$ = NULL ;}
	      | DEFINE MODULE module_definition
	      { $$ = NULL ;}
              ;

flags     : /* nothing */ 
              { $$ = open_class ; }
              | flags OPEN
              { $$ = (class_adjectives) ($1 | open_class), delete $2  ; }
              | flags SEALED
              { $$ = (class_adjectives) ($1 | sealed_class), delete $2  ; }
              | flags PRIMARY
              { $$ = (class_adjectives) ($1 | primary_class), delete $2  ; }
              | flags FREE
              { $$ =(class_adjectives)  ($1 | free_class), delete $2  ; }
              | flags CONCRETE
              { $$ = (class_adjectives) ($1 | concrete_class), delete $2  ; }
              | flags ABSTRACT
              { $$ = (class_adjectives) ($1 | abstract_class), delete $2  ; }
              ;
slot_adj_opt  : /* nothing */
              { $$ = noadj ; }
              | OPEN
              { $$ = open_slot ; }
              | SEALED
              { $$ = sealed ; }
              | INHERITED
              { $$ = inherited ; }
              ;

library_definition : SYMBOL library_clauses_opt END library_opt symbol_opt
		   ;

library_opt :
	    | LIBRARY
	    ;

library_clauses_opt :
		    | library_clauses
		    | library_clauses SEMICOLON
		    ;

library_clauses : use
		| export
		| library_clauses SEMICOLON use
		| library_clauses SEMICOLON export
		;

use : USE SYMBOL use_options
    ;

export : EXPORT variable_names
       ;

create : CREATE variable_names
       ;

use_options : 
	    | use_options COMMA use_option
	    ;

use_option : prefix_option
	   | import_option
	   | exclude_option
	   | rename_option
	   | export_option
	   ;

prefix_option : PREFIX_OPTION STRING
	      ;

import_option : IMPORT_OPTION ALL
	      | IMPORT_OPTION LBRACE import_opt RBRACE
	      ;

import_opt :
	   | imports
	   ;

imports : SYMBOL
	| SYMBOL ARROW SYMBOL
	| imports COMMA SYMBOL
	| imports COMMA SYMBOL ARROW SYMBOL
	;

exclude_option : EXCLUDE_OPTION variable_name_set
	       ;

export_option : EXPORT_OPTION ALL
	      | EXPORT_OPTION variable_name_set
              ;

rename_option :  RENAME_OPTION LBRACE RBRACE
	      |  RENAME_OPTION LBRACE rename_specs RBRACE
	      ;

rename_specs : SYMBOL ARROW SYMBOL 
	     | rename_specs COMMA SYMBOL ARROW SYMBOL
	     ;

variable_name_set : LBRACE RBRACE
		  | LBRACE variable_names RBRACE
		  ;

variable_names : SYMBOL
	       | variable_names COMMA SYMBOL
	       ;

module_definition : SYMBOL module_clauses_opt END module_opt symbol_opt
		  ;

module_opt :
	   | MODULE
	   ;

module_clauses_opt :
		   | module_clauses
		   | module_clauses SEMICOLON
		   ; 

module_clauses : use
	       | export
	       | create
	       | module_clauses SEMICOLON use
	       | module_clauses SEMICOLON export
	       | module_clauses SEMICOLON create
	       ;

method_definition : SYMBOL method_body END method_opt symbol_opt
                    {  if ( $1->name[0] == '\\' )
                       {
                          $2->SetName( $1->name + 1 ) ;
                       }
                       else
                       { 
                          $2->SetName( $1->name ) ;
                       }
                       $$ = $2 ; }
                  ;

method_body : LPAREN parameter_list_opt RPAREN semi_opt body
              { $$ = new Method( $2, (List<Variable *> *) NULL, $5 ) ;
                delete $1; delete $3 ; }
	    | LPAREN parameter_list_opt RPAREN ARROW variable SEMICOLON body
              { 
                $$ = new Method( $2, tempvar , $7) ;
                delete $1; delete $3; delete $4;
              }
	    | LPAREN parameter_list_opt RPAREN ARROW LPAREN variable_list_opt RPAREN SEMICOLON body
               { $$ = new Method( $2, $6, $9 ) ;
                 delete $1; delete $3; delete $4; delete $5; delete $7; delete $8;  }
	    ;

parameter_list_opt :
                   { $$ = NULL ; } 
		   | parameters
		   { $$ = $1 ; }
		   | parameters COMMA next_rest_key_parameter_list
		   { 
		     $1->Join($3) ;
		     $$ = $1 ;
		     $$->MoveTo(1) ;
		     $$->MoveTo(2) ;
		   }
		   | next_rest_key_parameter_list
		   { $$ = $1 ; }
                   ;

parameters : parameter
            { $$ = new List<Parameter *> ;
              $$->AppendItem($1) ;
            }
	   | parameters COMMA parameter
	     { $1->AppendItem( $3 ) ;
	       $$ = $1 ;
	       delete $2 ;
	     }
	   ;

parameter : variable
          { $$ = new Parameter( normal, $1->name, $1->type, NULL ) ; 
            VarDict.InsertVar($$, scope ) ; }
	  | SYMBOL EQUAL2 expression
          { $$ = new Parameter( singleton, $1->name, $3 ) ; 
            VarDict.InsertVar($$, scope ) ; } 
	  ;

next_rest_key_parameter_list : NEXT SYMBOL
                               { $$ = new List<Parameter *> ;
                                 $$->AppendItem( new Parameter( next_par, $2->name, (Expression *) NULL )) ; }
			     | NEXT SYMBOL COMMA rest_key_parameter_list
                             {  $4->AppendItem( new Parameter( next_par, $2->name, (Expression *) NULL )) ;
                                $$ = $4 ; }
			     | rest_key_parameter_list
			     { $$ = $1 ;
			        }
			     ;

rest_key_parameter_list :   REST SYMBOL
                          { $$ = new List<Parameter *> ;
                            temp = new Parameter( rest_par, $2->name, (Expression *) NULL ) ; 
                            VarDict.InsertVar(temp, scope ) ;
                            $$->AppendItem( temp ) ; }
			  | REST SYMBOL COMMA key_parameter_list
                          {  $$ = new List<Parameter *> ;
                             $$->AppendItem( new Parameter( rest_par, $2->name, (Expression *) NULL )) ; 
                             $$->Join($4) ; }
			  | key_parameter_list
			  { $$ = $1 ;
			     }
			     ;

key_parameter_list : KEY keyword_parameters_opt
                    { $$ = $2 ;
                       }
		   | KEY keyword_parameters_opt COMMA ALL_KEYS
                    { $$ = $2 ;
                      $$->AppendItem( new Parameter(all_keys_par, "all-keys", (Expression *) NULL)) ; }
		   | ALL_KEYS
                    { $$ = new List<Parameter *> ;
                      $$->AppendItem( new Parameter(all_keys_par, "all-keys", (Expression *) NULL)) ; }
                   ;

keyword_parameters_opt :
                       { $$ = NULL ;}
		       | keyword_parameter
		       { $$ = new List<Parameter *> ;
		         $$->AppendItem($1) ;
		       }
		       | keyword_parameters_opt COMMA keyword_parameter
		       { $1->AppendItem($3) ;
		         $$ = $1;
		       }
		       ;

keyword_parameter : KEYWORD SYMBOL default_opt
                   {
                      $$ = new Parameter(key_par, $2->name, $1->name, $3 ) ;
                      VarDict.InsertVar($$, scope ) ; }
		  | SYMBOL default_opt
                   { $$ = new Parameter(key_par, $1->name, $1->name, $2 ) ; 
                     VarDict.InsertVar($$, scope ) ; }
		  ;

default_opt :
            { $$ = NULL ; }
	    | LPAREN expression RPAREN
	    { $$ = $2 ; } 
	    ;

variable : SYMBOL
         {    
             $$  = new struct tempvar ; 
             $$->name = $1->name ;
             ClassDict.SearchClass("<object>") ;
             $$->type = new ConstRef(ClassDict.GetClass()) ;
             }
	 | SYMBOL COLON2 type
         {   $$  = new struct tempvar ;
             $$->name = $1->name ;
             $$->type = $3 ;
             }

	 ;

variable_list_opt : 
              { $$ = NULL ; }
	      | variable_list
	      { $$ = $1 ; }
	      ;

variable_list : variables
              { $$ = $1 ; }
	      | variables COMMA REST SYMBOL
              {  
                $1->AppendItem( new Variable( $4->name, -2) ) ;
                delete $2; delete $3 ;
              }
	      | REST SYMBOL
              { $$ = new List<Variable *> ;
                $$->AppendItem( new Variable( $2->name, -2) ) ;
                delete $1;
              }
	      ;

variables : variable
            { $$ = new List<Variable *> ;
              $$->AppendItem( new Variable( $1->name, $1->type) ) ;
            }
	  | variables COMMA variable
	    { $1->AppendItem( new Variable( $3->name, $3->type) ) ;
	      $$ = $1 ;
	      delete $2;
	    }
	  ;

type : operand
      {  char *object_type ;
         object_type = new char[255] ;
         $1->GetValue(NULL)->Getter(object_type) ;
         ClassDict.SearchClass( object_type) ;
         $$ = new ConstRef(ClassDict.GetClass()) ;
         delete object_type ; }
     ;

method_opt :
	   | METHOD
	   ;

generic_function_definition : SYMBOL generic_function_body property_list_opt
                              { $2->SetName($1->name) ;
                                $$ = $2 ;
                              } 
                            ;

bindings : variable EQUAL expression
         {  $$ = new Variable( $1->name, -1, $1->type ,$3,FALSE ) ;
            delete $1 ; }
	 | LPAREN variable_list RPAREN EQUAL expression
	 { int i ;
	   for( i = 1; i <= $2->GetSize(); i++ )
	   {
             $2->MoveTo(i) ;
             $2->GetItem()->SetIndex(i) ;
             $2->GetItem()->SetVar($5) ;
             if ( i != 1 ) VarDict.InsertVar($2->GetItem(), scope) ; 
	   }
           $2->MoveTo(1) ;
	   $$ = $2->GetItem() ;
         }
         ;

semi_opt :
	 | SEMICOLON
	 ;

generic_function_body : LPAREN parameter_list_opt RPAREN 
                        { $$ = new Method( $2, (List<Variable *> *) NULL ) ;
                          delete $1; delete $3 ; }
	    | LPAREN parameter_list_opt RPAREN ARROW variable
                        { $$ = new Method( $2, new Variable ($5->name, $5->type )) ;
                         delete $1; delete $3; delete $4; }
	    | LPAREN parameter_list_opt RPAREN ARROW LPAREN variable_list_opt RPAREN
                        { $$ = new Method( $2, $6 ) ;
                          delete $1; delete $3; delete $4; delete $5; }
	    ;

symbol_opt :
           { $$ = NULL ; }
	   | SYMBOL
	   { $$ = yylval.token ; }
	  
	   ;

local_declaration : LET bindings
                  { $$ = $2;
                    VarDict.InsertVar($2, scope) ; }
		  | LET HANDLER condition EQUAL handler
		  { $$ = NULL ; } 
		  | LOCAL local_methods
		  { $$ = $2 ; } 
		  ;

condition : type
	  | LPAREN type property_list_opt RPAREN
	  ;

handler : expression
	;

local_methods : method_opt method_definition
              { MethodDict.InsertMethod($2, scope) ;
                $$ = $2 ; }
	      | method_opt method_definition COMMA local_methods
	      { MethodDict.InsertMethod($2, scope) ;
	        $$ = $2 ; }
	      ;

expressions : expression
              { $$ = new List<Expression *> ;
                $$->AppendItem($1) ;
              } 
            | expressions COMMA expression
              { $1->AppendItem($3) ;
                $$ = $1 ;
              }
            ;

expression : binary_operand
             { $$ = $1 ; }
           | expression ADD expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression MINUS expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression DIV expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression MUL expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression ASSIGN expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression AND expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression OR expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression GT expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression LT expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression LE expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression GE expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression NE expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression EQUAL expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           | expression EQUAL2 expression
           { $$ = MakeExpression( $2->name, $1, $3 ) ; }
           ;

binary_operand : KEYWORD
               {  $$ = new ConstRef(new keyword( $1->name, NULL)) ;
               }
               | operand
               { $$ = $1 ; } ;
               | unary_operand
               { $$ = $1 ; } ;

class_definition : SYMBOL LPAREN superclasses RPAREN slot_specs_opt END class_opt symbol_opt
                   {  $$ = new class_type( $1->name, $3, $5 ) ; }
		 ;

class_opt :
	  | CLASS
	  ;

superclasses : expression
           {  char *object_type ;
              $$ = new List<DylanObject *> ;

              object_type = new char[255] ;

              $1->GetValue(NULL)->Getter(object_type) ;
              ClassDict.SearchClass( object_type) ;
              $$->AppendItem(ClassDict.GetClass()) ;
              delete object_type ; } 

	     | superclasses COMMA expression
	     { char *object_type ;

               object_type = new char[255] ;

               $3->GetValue(NULL)->Getter(object_type) ;
               ClassDict.SearchClass( object_type) ;
               $$->AppendItem(ClassDict.GetClass()) ;
	       $$ = $1 ; 
               delete object_type ;
	     }
	     ;

slot_specs_opt :
               { $$ = NULL ; }
	       | slot_specs SEMICOLON
	       { $$ = $1; }
	       ;

slot_specs : slot_spec 
            {  
              $$ = new List<Slot_specs *> ;
              $$->AppendItem($1) ; }
	   | slot_specs SEMICOLON slot_spec
            { delete $2 ;
              
              $1->AppendItem($3) ; 
              $$ = $1 ; }
	   ;

slot_spec : slot_adj_opt alloc_opt SLOT symbol_opt slot_type_opt property_list_opt
            { 
              $$=new Slot_specs( $1,$2,$4->name,$5,$6) ;
              delete $3 ; }  
	  ;

alloc_opt : 
          { $$ = noalloc ; }
	  | INSTANCE 
          { delete $1; $$ = instance ; }
	  | CLASS
          { delete $1; $$ = dylan_class ; }
	  | SUBCLASS
          { delete $1; $$ = subclass ; }
	  | CONSTANT
          { delete $1; $$ = constant_class ; }
	  | VIRTUAL
          { delete $1; $$ = virtual_class ; }
	  ;

slot_type_opt :
              { $$ = NULL ; }
	      | COLON2 expression
              {  char *object_type ;
                 object_type = new char[255] ;
                 $2->GetValue(NULL)->Getter(object_type) ;
                
                 ClassDict.SearchClass( object_type) ;
                 $$ = ClassDict.GetClass() ;
                 delete object_type ; 
                 delete $1 ; } 
	      ;

property_list_opt :
                  { $$ = NULL ; }
		  | property_list
		  { $$ = $1 ; }
		  ;

property_list : COMMA property
              { delete $1;
                $$ = new List<Property *> ;
                $$->AppendItem($2) ; }
	      | property_list COMMA property
              { delete $2;
                $1->AppendItem($3) ; 
                $$ = $1 ; }
              ;

property : KEYWORD value
           { $$->keyword =  $1->name;
             $$->value   = $2 ; } 
	 ;

value : expression
      { $$ = $1 ; }
      | LBRACE property_set_opt RBRACE
      { $$ = NULL ; }
      ;

property_set_opt :
		 | property_set
		 ;

property_set : property_set_member
	     | property_set COMMA property_set_member
	     ;

property_set_member : property_set_item
		    | property_set_item ARROW property_set_item
		    ;

property_set_item : SYMBOL
		  ;

unary_operand :  TILDE operand
                 { $$ = new Not ($2); delete $1 ; } 
                 | MINUS operand
                 { $$ = new Minus($2) ; delete $1 ;  } 
                 ;

operand : operand LBRACKET arguments RBRACKET
          { $$ = new VectorRef( $1, $3) ; delete $2; delete $4; }
          | operand LPAREN arguments_opt RPAREN
          { $$ = new MethodRef( $1, $3); delete $2; delete $4; } 
          | operand PERIOD SYMBOL
          { $$ = new ClassRef( $1, $3->name) ; }
          | leaf
	       { $$ = $1 ; }
	;

arguments_opt :
              { $$ = NULL ; }
	      | arguments
	      { $$ = $1 ; }
	      ;

arguments : argument
           { $$ = new List<Argument *> ;
             $$->AppendItem($1) ;
           }
	  | arguments COMMA argument
	  { $1->AppendItem($3) ;
	    $$ = $1 ;
	  }
	  ;

argument : expression
         { $$ = new Argument($1) ; }
	 | KEYWORD expression
         { $$ = new Argument($2, $1->name) ; }
	 ;

leaf : literal
     { $$ = new ConstRef($1) ; }
     | SYMBOL
     { ForParse = new Variable( $1->name, 0 ) ; 
       if ( VarDict.SearchVar(ForParse, scope) )
       { 
          $$ = new VarRef(VarDict.GetVar()) ;
       }
       else if ( $1->name[0] == '\\' &&
                 MethodDict.SearchMethod($1->name + 1, NULL, NULL, NULL, NULL ) )
       {
         Function = new function (MethodDict.GetMethod()) ;
         $$ = new ConstRef(Function) ;
       }
       else 
       {
         Symbol = new symbol ($1->name) ;
         $$ = new ConstRef(Symbol) ;
       }
       delete ForParse ;
     }
     | LPAREN expression RPAREN
     { $$ = new Subexp($2) ; delete $1; delete $3 ; }
     | anonymous_method
     { $$ = $1 ; }
     | statement
     { $$ = $1 ;}
     ;

anonymous_method : METHOD {scope++ ; } method_body END METHOD
                 { $$ = $3 ; 
                   scope-- ;
                   delete $1; 
                   delete $4; 
                   delete $5; 
                   VarDict.InsertVar( Sentinel, scope ) ; } ;

literal : CHAR_LIT
	{ $$ = new character( yylval.token->name[1])  ; }
	| STRING
	{ $$ = new string( yylval.token->name)  ; }
	| BTRUE
	{ $$ = new boolean_type (1)  ; }
	| BFALSE
	{ $$ = new boolean_type (0) ; }
	| INTEGER
	{ $$ = new integer( MakeInteger( yylval.token->name) ) ; }
	| FLOAT
	{ $$ = new double_float( MakeReal (yylval.token->name) ) ; }
	| RATIO
	{ $$ = NULL ; }
	| LIST_LIT constants PERIOD constant RPAREN
	{ delete $1; $$ = NULL ; delete $3; delete $4 ; }
	| LIST_LIT constants_opt RPAREN
	{ $$ = new list($2) ; delete $1; delete $3; }
	| VECTOR_LIT constants_opt RBRACKET
	{ $$ = new vector($2) ; delete $1; delete $3; }
	;

constants_opt :
              { $$ = NULL ; }
	      | constants
              { $$ = $1 ; }
	      ;

constants : constant
	   { $$ = new List<DylanObject *> ; 
	     $$->AppendItem($1) ; }
	  | constants COMMA constant
	  { $1->AppendItem($3) ;
	    $$ = $1;
	    delete $2 ; } 
	  ;

constant : literal
         { $$ = $1 ; }  
         | KEYWORD
	 { $$ = new string( yylval.token->name) ; }
	 ;
statement : IF LPAREN expression RPAREN {scope++ ; } then_part else_part END end_if
            { $$ = new If( $3, $6, $7 )  ;  scope-- ;VarDict.InsertVar(Sentinel, scope ) ; }
          | WHILE LPAREN expression RPAREN {scope++ ; } body END end_while
          { $$ = new While( $3, $6 ) ; scope-- ; VarDict.InsertVar(Sentinel, scope) ; }
          | UNLESS LPAREN expression RPAREN {scope++ ; } body END end_unless
          { $$ = new Unless( $3, $6 ) ; scope-- ; VarDict.InsertVar(Sentinel, scope) ; }
          | UNTIL LPAREN expression RPAREN {scope++ ; } body END end_until
          { $$ = new Until( $3, $6 ) ; scope-- ; VarDict.InsertVar(Sentinel, scope) ; }
          | CASE {scope++ ; } case_body END end_case
          { $$ = new Case( $3->tests, $3->bodies ) ; VarDict.InsertVar(Sentinel, scope) ; }
          | SELECT LPAREN expression RPAREN {scope++ ; } select_body END end_select
          { $$ = new Select( $3, $6 ) ; scope-- ; VarDict.InsertVar(Sentinel, scope) ; }
          | FOR {scope++ ; } for_body END end_for
          { $$ = $3 ; scope-- ; VarDict.InsertVar(Sentinel, scope) ; }
          | MYBEGIN {scope++ ; } body END end_begin
          { $$ = new Begin( $3 ) ; delete $1; delete $4 ;scope-- ; VarDict.InsertVar(Sentinel, scope) ;  }
          | BLOCK LPAREN variable_opt RPAREN block_body END end_block  
          { $$ = NULL ; }
          ;

variable_opt :
             | variable
             ;

then_part : body
            { $$ = $1 ; }
          ;

else_part :
          { $$ = NULL ; }
          | ELSE body
          { $$ = $2 ; }
          | elseif_part
          { $$ = $1 ; }
          ;

elseif_part : ELSEIF LPAREN expression RPAREN body else_part
            { $$ = new Body ;
              $$->AppendConstituent( new If($3,$5,$6)) ;
            }
          ;

end_block : 
          | BLOCK
          ;
end_for  : 
          | FOR
         ;

end_select : 
           | SELECT
           ;

end_if : 
         | IF
       ;
end_unless : 
          | UNLESS
           ;

end_until : 
           | UNTIL
          ;

end_while : 
           | WHILE
          ;
end_begin : 
           | MYBEGIN
          ;

end_case : 
          | CASE
         ;

case_body : case_label body_label  SEMICOLON
           { $$ = new CaseBody ;
             $$->tests = new List<Expression *> ;
             $$->bodies = new List<Body *> ;
             $$->tests->AppendItem($1) ;
             $$->bodies->AppendItem($2) ;
           }
           | case_body case_label body_label SEMICOLON
          {
             $1->tests->AppendItem($2) ;
             $1->bodies->AppendItem($3) ;
             $$ = $1 ;
          }
          ;

body_label : body
           { $$ = $1 ; } 
           ;

case_label : expression ARROW
           { $$ = $1 ; delete $2; }
           | OTHERWISE ARROW
           { $$ = NULL ; delete $1; delete $2; } 
           ;

select_body : 
             { $$ = NULL ; }
             | select_label body
             { $$ = new List<SelectElement *> ;
               $$->AppendItem( new SelectElement($1,$2) ) ;
             }  
             | select_body SEMICOLON select_label body 
             { $1->AppendItem(new SelectElement($3,$4)) ;
               $$ = $1 ;
             }  
          ;

select_label : expressions ARROW
           { $$ = $1 ; delete $2 ; }
           | OTHERWISE arrow_opt
           { $$ = NULL; delete $1; }
           ;

arrow_opt :
	  | ARROW
	  ;

for_body : LPAREN clauses COMMA UNTIL expression RPAREN body finally_opt
         { $$ = new For( $2, $5, until_test, $7, $8 ) ; }  
         | LPAREN clauses COMMA WHILE expression RPAREN body finally_opt
         { $$ = new For( $2, $5, while_test, $7, $8 ) ; }  
         | LPAREN clauses RPAREN body finally_opt
         { $$ = new For( $2, $4, $5 ) ; }  
         ;

clauses : clause 
        { $$ = new List<Clause *> ;
          $$->AppendItem($1) ;
        }
        | clauses COMMA clause
        { $1->AppendItem($3 ) ;
          $$ = $1 ;
          delete $2 ;
        }
        ;

clause : variable EQUAL expression 
       { tempvar = new Variable( $1->name, -1, $1->type, $3, FALSE ) ;
         VarDict.InsertVar( tempvar, scope ) ;
       } THEN expression
       { $$ = new Explicit_clause( tempvar, $3, $6 ) ; delete $2; delete $5; }
       | variable IN expression
       { tempvar = new Variable( $1->name, -1, $1->type, $3, FALSE ) ;
         VarDict.InsertVar( tempvar, scope ) ;
         $$ = new Collection_clause( tempvar, $3 ) ; delete $2 ; }
       | variable FROM expression bound_opt increment_opt
       { tempvar = new Variable( $1->name, -1, $1->type, $3, FALSE ) ;
         VarDict.InsertVar( tempvar, scope ) ;
         $$ = new Numeric_clause( tempvar, $3, $4, $5 ) ; delete $2 ; }
       ;

bound_opt: 
         { $$ = NULL ; }
         | TO expression
         { $$ = new To($2); delete $1;  }
         | ABOVE expression
         { $$ =  new Above($2); delete $1;  }
         | BELOW expression
         { $$ =  new Below($2); delete $1;  }
         ;

increment_opt :
              { $$ = NULL ; }
              | BY expression
              { $$ = $2 ; delete $1; }
              ;

finally_opt : 
            { $$ = NULL ; } 
            | FINALLY body
            { $$ = $2 ; delete $1 ;} 
            ;

block_body : body cleanup_opt exception_opt
           ;

cleanup_opt :
            | CLEANUP body
            ;

exception_opt :
              | exceptions
              ;

exceptions : exception
           | exceptions exception
           ;

exception : EXCEPTION body
          ;
%%

#include "lex.yy.c"

void yyerror(const char *s)
{
   fprintf( stderr, "%s : %s in line %d \n", s, yytext, linecount ) ;
   exit(-1) ;
}     
/*
int yywrap()
{
    return(1) ;
}*/
