#ifndef _SYNTAX_H_
#define _SYNTAX_H_

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


    EXPR,
    END,
    UNKNOWN,
};


extern int yylval;
extern int tok;


#endif