LEX = lex
YACC = bison
CC = g++
CFLAGS = -std=c++11
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs core`

all: main


main: main.cpp parser.cpp tokens.cpp codegen.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LLVMFLAGS)

parser.cpp: parser.y
	$(YACC) -d -o $@ $^
	
parser.hpp: parser.cpp

tokens.cpp: tokens.l parser.hpp
	$(LEX) -o $@ $^



.PHONY:
clean:
	rm main parser.cpp parser.hpp tokens.cpp



