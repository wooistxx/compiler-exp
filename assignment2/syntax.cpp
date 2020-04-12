#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ast.h"
#include "syntax.h"



using namespace std;

int yylval;
int tok;


extern int yylex();
extern char * yytext;
extern FILE * yyin;

void program(shared_ptr<NBlock>);
void pprogram(shared_ptr<NBlock>);
void stats(shared_ptr<NBlock>);
void assignment(shared_ptr<NAssignment>);
void e(shared_ptr<NE>);
void ee(shared_ptr<NEE>);
void t(shared_ptr<NT>);
void tt(shared_ptr<NTT>);
void f(shared_ptr<NF>);


// ==========================================================================================================================

shared_ptr<NBlock> globalBlock = make_shared<NBlock>();




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

    tok = yylex();
    program(globalBlock);

    cout << "==================================" << endl;
    globalBlock->print();

    return 0;
}



void program(shared_ptr<NBlock> n)
{
    pprogram(n);
}



void pprogram(shared_ptr<NBlock> n)
{
    stats(n);
    cout << ".";
    tok = yylex();
    if(tok == IDENTITY || tok == EOL)
        pprogram(n);
    else
        cout << "error pprogram "  << tok << endl;
}

void stats(shared_ptr<NBlock> n)
{
    if(tok == IDENTITY)
    {
        // string identity = string(yytext);
        NIdent * _nident = new NIdent(yytext);
        shared_ptr<NIdent> nident(_nident);
        tok = yylex();
        if(tok == EQUAL) /* IDENTITY EQUAL => assignment */
        {
            NAssignment * _nassi = new NAssignment();
            _nassi->l = nident;
            shared_ptr<NAssignment> nassi(_nassi);
            tok = yylex();
            assignment(nassi);
            n->statslist->push_back(nassi);
        }
        else if(tok == LPAREN) /* IDENTITY LPAREN => funcall */
        {

        }
    }
}


void assignment(shared_ptr<NAssignment> n)
{
    if(tok == LBRACE) // 是数组定义, 暂时不支持
    {
        tok = yylex();
    }
    else // 认为是表达式
    {
        NE * _ne = new NE();
        shared_ptr<NE> ne(_ne);
        n->r = ne;

        e(ne);
    }
}

void e(shared_ptr<NE>  n)
{
    NT * _nt = new NT();
    shared_ptr<NT> nt(_nt);

    NEE * _nee = new NEE();
    shared_ptr<NEE> nee(_nee);
    nee->op = 0;
    
    n->l = nt;
    n->r = nee;
    
    t(nt);
    ee(nee);
}

void ee(shared_ptr<NEE> n)
{
    if(tok == PLUS)
    {
        NT * _nt = new NT();
        shared_ptr<NT> nt(_nt);

        NEE * _nee = new NEE();
        shared_ptr<NEE> nee(_nee);
        nee->op = 0;

        n->op = PLUS;
        n->l = nt;
        n->r = nee;

        tok = yylex();
        t(nt);
        ee(nee);
    }
    else if(tok != EOL && tok != RPAREN)
    {
        cout << "e' error : " << yytext << " " <<  tok << endl;
    }
}

void t(shared_ptr<NT> n)
{
    NF * _nf = new NF();
    shared_ptr<NF> nf(_nf);

    NTT * _ntt = new NTT();
    shared_ptr<NTT> ntt(_ntt);

    n->l = nf;
    n->r = ntt;

    f(nf);
    tt(ntt);
}


void tt(shared_ptr<NTT> n)
{
    if(tok == TIMES)
    {
        NF * _nf = new NF();
        shared_ptr<NF> nf(_nf);

        NTT * _ntt = new NTT();
        shared_ptr<NTT> ntt(_ntt);

        n->op = tok;
        n->l = nf;
        n->r = ntt;

        tok = yylex();
        f(nf);
        tt(ntt);

    }
    else if(tok != EOL && tok != RPAREN && tok != PLUS)
    {
        cout << "t' error : " << yytext << " " << tok << endl;
    }
}



void f(shared_ptr<NF> n)
{
    if(tok == IDENTITY)
    {
        NIdent * _nident = new NIdent(yytext);
        shared_ptr<NIdent> nident(_nident);
        n->l = nident;
        n->r = nullptr;
        n->op = IDENTITY;

        tok = yylex();
    }
    else if(tok == NUMBER)
    {
        NInteger * _nint = new NInteger(atoi(yytext));
        shared_ptr<NInteger> nint(_nint);
        n->l = nint;
        n->r = nullptr;
        n->op = NUMBER;

        tok = yylex();
    }
    else
    {
        if(tok == LPAREN)
        {
            NE * _ne = new NE();
            shared_ptr<NE> ne(_ne);
            // n->l = ne;
            // n->r = nullptr;
            n->op = EXPR;


            tok = yylex();

            e(ne);
            if(tok = RPAREN)
            {
                tok = yylex();
            }
            else
            {
                cout << "f error (1)" << endl;
            }
        }
        else
        {
            cout << "f error (2)" << endl;
        }
    }
}




