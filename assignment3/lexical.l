%{
    #include <iostream>
    #include "syntax.h"
    //extern int yylval;

%}



%% // Rules Section --------------------------------------------------
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return SLASH; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"["                 { return LBRACKET; }
"]"                 { return RBRACKET; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"="                 { return EQUAL; }
[0-9]+              { yylval = atoi(yytext); return NUMBER; }
\n                  { return EOL; }
[ \t]               { } //忽略空白符
"END"               { return END; }
[a-zA-Z1-9]+        { return IDENTITY; }	
.                   { return UNKNOWN; }

%% // User Subroutines Section --------------------------------------------------


int yywrap()
{
    // %option noyywrap
    std::cout << "file is over!" << std::endl;
    return 1;
}

