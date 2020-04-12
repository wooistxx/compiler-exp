#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include <vector>
#include <string>

using namespace std;

enum yytokentype{
    NUMBER  = 258,
    IDENTITY,
    PLUS,
    MINUS,
    TIMES,
    SLASH,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    EQUAL,
    EOL,
//---------------------------
    PROGRAM,
    PPROGRAM,
    STATS,
    IDENTSTATS,
    ASSIGNMENT,
    FUNCALL,
    E,
    EE,
    T,
    TT,
    F,

//-------------------------------

    END,
    UNKNOWN,
};



extern vector<string> reToken;
extern int yylval;
extern int tok;


#endif