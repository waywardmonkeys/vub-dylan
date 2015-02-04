# makefile voor de dylan programmeer taal 
# datum : 15/08/1994
CC=g++ -x c++ -O2 -g
CCLIBS= -ldylan -lgc -lm 
LEX=flex
YACC=yacc -t
OBJS=class.o \
     expression.o \
     variable.o \
     body.o \
     statement.o \
     method.o \
     primitive.o \
     object.o\
     keyword.o\
     boolean.o\
     character.o\
     class_type.o\
     double_float.o\
     extended_float.o\
     float.o\
     function.o\
     integer.o\
     number.o\
     rational.o\
     real.o\
     single_float.o\
     slot.o\
     symbol.o\
     type.o\
     array.o\
     vector.o\
     range.o\
     list_type.o\
     collection.o\
     mutable_sequence.o\
     rest_list.o\
     sequence.o\
     string.o\
     values_list.o\
     environment.o\
     apply.o

all : dylan

lex.yy.c : dylan.lex
	$(LEX) dylan.lex

y.tab.c : dylan.yacc lex.yy.c 
	$(YACC) dylan.yacc

dylan : y.tab.c dylan.c object.h libdylan.a
	$(CC) dylan.c -o dylan -L. $(CCLIBS)

libdylan.a : $(OBJS) list.h
	ar -ru libdylan.a $(OBJS)
	ranlib libdylan.a

expression.o : expression.c expression.h object.h
	$(CC) -c expression.c

class.o : class.c class.h object.h
	$(CC) -c class.c

variable.o : variable.c variable.h object.h
	$(CC) -c variable.c

body.o : body.c body.h expression.h
	$(CC) -c body.c

statement.o : statement.c statement.h expression.h
	$(CC) -c statement.c

method.o : method.c method.h expression.h object.h
	$(CC) -c method.c

primitive.o : primitive.c primitive.h object.h
	$(CC) -c primitive.c

object.o : object.c object.h
	$(CC) -c object.c

keyword.o : keyword.c object.h
	$(CC) -c keyword.c
	
boolean.o : boolean.c object.h
	$(CC) -c boolean.c

character.o : character.c object.h
	$(CC) -c character.c

class_type.o : class_type.c object.h
	$(CC) -c class_type.c

double_float.o : double_float.c object.h
	$(CC) -c double_float.c

extended_float.o : extended_float.c object.h
	$(CC) -c extended_float.c

float.o : float.c object.h
	$(CC) -c float.c

function.o : function.c object.h
	$(CC) -c function.c

integer.o : integer.c object.h
	$(CC) -c integer.c

number.o : number.c object.h
	$(CC) -c number.c

rational.o : rational.c object.h
	$(CC) -c rational.c

real.o : real.c object.h
	$(CC) -c real.c

single_float.o : single_float.c object.h
	$(CC) -c single_float.c

slot.o : slot.c object.h
	$(CC) -c slot.c

symbol.o : symbol.c object.h
	$(CC) -c symbol.c

type.o : type.c object.h
	$(CC) -c type.c

array.o : array.c object.h
	$(CC) -c array.c

vector.o : vector.c object.h
	$(CC) -c vector.c

range.o : range.c object.h
	$(CC) -c range.c

list_type.o : list_type.c object.h
	$(CC) -c list_type.c

collection.o : collection.c object.h
	$(CC) -c collection.c

mutable_sequence.o : mutable_sequence.c object.h
	$(CC) -c mutable_sequence.c

rest_list.o : rest_list.c object.h
	$(CC) -c rest_list.c

sequence.o : sequence.c object.h
	$(CC) -c sequence.c

string.o : string.c object.h
	$(CC) -c string.c

values_list.o : values_list.c object.h
	$(CC) -c values_list.c

environment.o : environment.c object.h variable.h environment.h
	$(CC) -c environment.c

apply.o : apply.c object.h apply.h environment.h method.h expression.h
	$(CC) -c apply.c
