
/*
 +------------------------------------------------------------------
 | FILENAME  : dylan.lex
 | DATE      : 01/09/1994
 |
 | ABSTRACT  : Lexicale analyzer dylan.
 |
 | CHANGES   :
 +------------------------------------------------------------------
*/
%{
#include "tokens.h"

struct Token_Struct *MyToken ;

int linecount = 1 ;

#define install_token(x) \
   { yylval.token = MakeToken( yytext, yyleng, x ) ; return x;} 

static struct Token_Struct *MakeToken( char *text, int length, int type ) ;
static int strcnt(char *) ;
%}

delim		[ \t]
semicolon	";"
nextline	[\n]
ws		{delim}+
alphabetic	[A-Za-z]
numeric		[0-9]
graphic 	[!&*<=>|^$%@_]
special 	[\-+~\?/]
unary_op	[~]
binary_op       "+"|"-"|"*"|"/"|"^"|"=="|"="|"~="|"<="|"<"|">="|">"|"&"|"|"|":="
op_symbol	{unary_op}|{binary_op}
any		{alphabetic}*{numeric}*{graphic}*{special}*
leading_numeric {numeric}|{numeric}{any}*
leading_graphic {graphic}|{graphic}{any}*
leading_alpha 	{alphabetic}|{alphabetic}{any}*
escape-char	[\\abefnrt0]
string-char	[^\"\\]|\\{escape-char}|\\\"
more-string	{string-char}*\"
string 		\"{more-string}
symbol  	{leading_graphic}|{leading_alpha}|{leading_numeric}{alphabetic}{leading_alpha}|\\{op_symbol}
keyword		{symbol}:|"#"{string}
bin-int		\#b[01]+
oct-int		\#o[0-7]+
dec-int		[+\-]?{numeric}+
hex-int		\#x[0-9A-F]+
integer		{bin-int}|{oct-int}|{dec-int}|{hex-int}
ratio		[+\-]?{dec-int}[/]{dec-int}
float           [+\-]?{numeric}+(\.{numeric}*)?(E[+\-]?{numeric}+)?
character	[^'\\]?|(\\{escape-char})?|(\\')?
char-literal    '{character}'
punctuation     \(|\)|,|\.|;|\[|\]|\{|\}|::|\-|=|==|=>|\#\(|\#\[|\?|\?\?|\.\.\.
true		"#t"
false		"#f"
next		"#next"
rest		"#rest"
key		"#key"
all-keys	"#all-keys"
comment-line    \/\/[ -~]*[\n]
comment-block   \/\*[ -~\n\t]*\*\/

%%
{ws}	/* do nothing */
{nextline}      { linecount++ ; }
{comment-line}  {linecount++ ; } /* skip comment lines */ 
{comment-block} { linecount += strcnt(yytext ) ; } 
"("		install_token(LPAREN);
")"		install_token(RPAREN);
","		install_token(COMMA);
"."		install_token(PERIOD);
";"		install_token(SEMICOLON);
"["		install_token(LBRACKET);
"]"		install_token(RBRACKET);
"{"		install_token(LBRACE);
"}"		install_token(RBRACE);
"::"		install_token(COLON2);
"="		install_token(EQUAL);
"-"		install_token(MINUS);
"+"		install_token(ADD);
"*"		install_token(MUL);
"/"		install_token(DIV);
":="		install_token(ASSIGN);
">"		install_token(GT);
"<"		install_token(LT);
">="		install_token(GE);
"<="		install_token(LE);
"~="		install_token(NE);
"&"		install_token(AND);
"|"		install_token(OR);
"=="		install_token(EQUAL2);
"=>"		install_token(ARROW);
"#("		install_token(LIST_LIT);
"#["		install_token(VECTOR_LIT);
"?"		install_token(QMARK);
"??"		install_token(QMARK2);
"..."		install_token(DOTS3);
"~"             install_token(TILDE);
above  		install_token(ABOVE);
begin   	install_token(MYBEGIN);
below 		install_token(BELOW) ;
block		install_token(BLOCK) ;
by  		install_token(BY)	;
case  		install_token(CASE)	;
class 		install_token(CLASS) ;
cleanup 	install_token(CLEANUP) ;
constant	install_token(CONSTANT) ;
define 		install_token(DEFINE) ;
elseif		install_token(ELSEIF) ;
else  		install_token(ELSE) ;
end  		install_token(END)	;
exception 	install_token(EXCEPTION) ;
finally 	install_token(FINALLY) ;
for  		install_token(FOR)	;
from 		install_token(FROM) ;
generic		install_token(GENERIC) ;
handler		install_token(HANDLER) ;
if  		install_token(IF)	;
in		install_token(IN)  	;
instance	install_token(INSTANCE) ;
let 		install_token(LET) ;
local 		install_token(LOCAL) ;
method  	install_token(METHOD)	;
otherwise 	install_token(OTHERWISE) ;
select 		install_token(SELECT) ;
slot  		install_token(SLOT)	;
subclass 	install_token(SUBCLASS) ;
then  		install_token(THEN)	;
to 		install_token(TO) ;
unless  	install_token(UNLESS)	;
until  		install_token(UNTIL)	;
variable	install_token(VARIABLE) ;
virtual 	install_token(VIRTUAL) ;
while  		install_token(WHILE)	;
create  	install_token(CREATE)	;
export  	install_token(EXPORT)	;
import  	install_token(IMPORT)	;
use  		install_token(USE)	;
module  	install_token(MODULE)	;
library  	install_token(LIBRARY)	;
all  		install_token(ALL)	;
inherited       install_token(INHERITED) ;
abstract        install_token(ABSTRACT) ;
{binary_op} install_token(BIN_OP) ;
{symbol}	install_token(SYMBOL) ;
{keyword}	install_token(KEYWORD) ;
{integer}	install_token(INTEGER) ;
{float}		install_token(FLOAT) ;
{ratio}		install_token(RATIO) ;
{char-literal}	install_token(CHAR_LIT);
{string}	install_token(STRING)	;
{true}	        install_token(BTRUE)	;
{false}	        install_token(BFALSE)	;
{next}	        install_token(NEXT)	;
{rest}	        install_token(REST)	;
{key}	        install_token(KEY)	;
{all-keys}      install_token(ALL_KEYS)	;
%%

static int strcnt( char *s )
{
   int i ;
   int j ; 

   i = 0 ;
   j = 0 ;
   while ( s[i] != '\0' )
   {
      if ( s[i] == '\n' ) j++ ;
      i++ ;
   }
   return j ;
}

static struct Token_Struct *MakeToken( char *text, int length, int type )
{
   struct Token_Struct *AToken ;

   AToken = new struct Token_Struct ;
   AToken->length = length ;
   AToken->type   = type ;
   AToken->lineno = linecount ;
   AToken->name   = new char[length + 1];
   strcpy( AToken->name, text ) ;
   return AToken ;
}
