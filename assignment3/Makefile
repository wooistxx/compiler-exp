

LEX=flex
CC=g++
CFLAGS= -ggdb -std=c++11

.PHONY:
all: syntax lex.yy.c


syntax: syntax.cpp lex.yy.c
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.c: lexical.l
	$(LEX) $<

.PHONY:
exe: syntax
	./syntax

.PHONY:
clean:
	rm syntax lex.yy.c 





