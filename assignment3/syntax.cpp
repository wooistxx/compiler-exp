#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stack>
#include "syntax.h"
#include "syntaxstack.h"


using namespace std;

int yylval;
int tok;


extern int yylex();
extern char * yytext;
extern FILE * yyin;

void init();

// ==========================================================================================================================
vector<string> reToken(0);


int main(int argc, char * argv[])
{
    string filename;
    cout << "please input your filename : ";
    cin >> filename;
    yyin = fopen(filename.c_str(), "r");
    if(yyin == NULL)
    {
        cout << "file opne failed!" << endl;
    }
//===================================================================================
    init();
    SyntaxStack s;
    s.push(PROGRAM);
    tok = yylex();
    s.print();
    while(true)
    {
        enum yytokentype x = s.pop();
        if(x == tok)
        {
            cout << "------------------" << reToken[tok] << " " << yytext << endl;

            tok = yylex();
            if(x == EOL && tok == 0)
            {
                cout << "compiler over ! ----------------" << endl;
                break;
            }
            else if(x == EOL)
            {
                cout << tok << " " << reToken[tok] << endl;
            }
        }
        else if(x == PROGRAM && tok == IDENTITY)
        {
            s.push(PPROGRAM);
        }
        else if(x == PPROGRAM && tok == IDENTITY)
        {
            s.push(PPROGRAM);
            s.push(EOL);
            s.push(STATS);
        }
        else if(x == STATS && tok == IDENTITY)
        {
            s.push(IDENTSTATS);
            s.push(IDENTITY);
        }
        else if(x == IDENTSTATS && tok == EQUAL)
        {
            s.push(E);
            s.push(EQUAL);
        }
        else if(x == IDENTSTATS && tok == LPAREN)
        {
            s.push(RPAREN);
            s.push(LPAREN);
        }
        else if(x == E && (tok == LPAREN || tok == IDENTITY || tok == NUMBER))
        {
            s.push(EE);
            s.push(T);
        }
        else if(x == EE && tok == PLUS)
        {
            s.push(EE);
            s.push(T);
            s.push(PLUS);
        }
        else if(x == EE && (tok == EOL || tok == RPAREN))
        {}
        else if(x == T && (tok == LPAREN || tok == IDENTITY || tok == NUMBER))
        {
            s.push(TT);
            s.push(F);
        }
        else if(x == TT && tok == TIMES)
        {
            s.push(TT);
            s.push(F);
            s.push(TIMES);
        }
        else if(x == TT && (tok == PLUS || tok == EOL || tok == LPAREN))
        {}
        else if(x == F && (tok == LPAREN)) //|| tok == IDENTITY || tok == NUMBER
        {
            s.push(RPAREN);
            s.push(E);
            s.push(LPAREN);
        }
        else if(x == F && tok == IDENTITY)
        {
            s.push(IDENTITY);
        }
        else if(x == F && tok == NUMBER)
        {
            s.push(NUMBER);
        }
        else
        {
            cout << "error : " << x  << " " << reToken[x] 
            << ", " << tok << " " << reToken[tok] << " " << yytext << endl;
        }
        s.print();
    }



    return 0;
}



void init()
{
// ---        (.*), 
// reGS[GS::$1] = "$1";
// reGS.insert(pair<GS, string>(GS::$1, "$1"));
// reGS.insert(map<GS, string>::value_type(GS::$1, "$1"));



    for(int i=0;i<258;i++)
        reToken.push_back("yydef");
    //           (.*), 
    // reToken.push_back("$1");

reToken.push_back("NUMBER");
reToken.push_back("IDENTITY");
reToken.push_back("PLUS");
reToken.push_back("MINUS");
reToken.push_back("TIMES");
reToken.push_back("SLASH");
reToken.push_back("LPAREN");
reToken.push_back("RPAREN");
reToken.push_back("LBRACKET");
reToken.push_back("RBRACKET");
reToken.push_back("LBRACE");
reToken.push_back("RBRACE");
reToken.push_back("EQUAL");
reToken.push_back("EOL");
reToken.push_back("PROGRAM");
reToken.push_back("PPROGRAM");
reToken.push_back("STATS");
reToken.push_back("IDENTSTATS");
reToken.push_back("ASSIGNMENT");
reToken.push_back("FUNCALL");
reToken.push_back("E");
reToken.push_back("EE");
reToken.push_back("T");
reToken.push_back("TT");
reToken.push_back("F");
reToken.push_back("END");
reToken.push_back("UNKNOWN");

}

