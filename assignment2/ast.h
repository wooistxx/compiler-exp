
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "syntax.h"

using namespace std;

class AstNode;
//class NStats;
class NExpr;
class NAssignment;
class NIdent;
class NBinaryOp;
class NE;
class NEE;
class NT;
class NTT;
class NF;
class NBlock;


// typedef vector<shared_ptr<NStats> > NStatsList;
typedef vector<shared_ptr<NExpr> > NStatsList;

class AstNode
{
public:
    AstNode(){}
protected:
    virtual ~AstNode(){}
    virtual void print() const 
    {
        cout << "AstNode" << endl;
    }
    
};


// class NStats : public AstNode
// {
// public:
// 	NStats(){}

// };


class NExpr : public AstNode
{
public:
    NExpr(){}

    virtual void print() const
    {
        cout << "NExpr" << endl;
    }
};




class NIdent : public NExpr
{
public:
    string name;
    bool isArray = false;
    
    NIdent(){}

    NIdent(const string name, bool isArray = false) :
    name(name), isArray(isArray)
    {}
    
    virtual void print() const
    {
        cout << "Ident\t - " << this << " - (name=" << name << ", isArray=" << isArray << ")" << endl;
    }
        
};



class NInteger : public NExpr
{
public:
    uint64_t v;

    NInteger(){}

    NInteger(uint64_t v) : 
    v(v){}

    virtual void print() const
    {
        cout << "Integer\t - " << this << " - (value=" << v << ")" << endl;
    }


};


class NAssignment : public NExpr
{
public:
    NAssignment(){}


    shared_ptr<NIdent> l;
    shared_ptr<NExpr>  r;
    
    virtual void print() const
    {
        cout << "Assigin\t - " << this << " - (ident=" << l << ", expr=" << r << ")" << endl;
        l->print();
        r->print();

    }
};


class NBinaryOp : public NExpr
{
public:
    int op;
    shared_ptr<NExpr> l;
    shared_ptr<NExpr> r;
    
    
    NBinaryOp(){}
    
    NBinaryOp(int op, shared_ptr<NExpr> l = nullptr, shared_ptr<NExpr> r = nullptr) : 
    op(op), l(l), r(r)
    {}
    
    virtual void print() const
    {
        cout << "NBinaryOp" << endl;
    }
};

class NE  : public NBinaryOp
{
public:
    NE(){}

    virtual void print() const
    {
        cout << "E\t - " << this << " - " << "(left=" << l << ", right=" << r << ")" << endl;
        if(l != nullptr) l->print();
        if(r != nullptr) r->print();
    }
};

class NEE : public NBinaryOp
{
public:
    NEE(){}
    virtual void print() const
    {
        cout << "EE\t - " << this << " - " << "(left=" << l << ", right=" << r << ", op=" << (op == PLUS? "+" : "?") <<  ")" << endl;
        if(l != nullptr) l->print();
        if(r != nullptr) r->print();
    }
};

class NT  : public NBinaryOp
{
public:
    NT(){}
    virtual void print() const
    {
        cout << "T\t - " << this << " - " << "(left=" << l << ", right=" << r << ")" << endl;
        if(l != nullptr) l->print();
        if(r != nullptr) r->print();
    }
};

class NTT : public NBinaryOp
{
public:
    NTT(){}

    virtual void print() const
    {
        cout << "TT\t - " << this << " - " << "(left=" << l << ", right=" << r << ", op=" << (op == TIMES? "x" : "?") <<  ")" << endl;
        if(l != nullptr) l->print();
        if(r != nullptr) r->print();
    }
};

class NF  : public NBinaryOp
{
public: 
    NF(){}

    virtual void print() const
    {
        cout << "F\t - " << this << " - " << "(";
        if(op == IDENTITY)
        {
            cout << "ident) => \n\t\t\t\t\t\t";
            l->print();
        }
        if(op == NUMBER)
        {
            cout << "num) => \n\t\t\t\t\t\t";
            l->print();
        }
    }
};





class NBlock : public NExpr
{
public:
    NBlock()
    {
        statslist = make_shared<NStatsList>();
    }

    shared_ptr<NStatsList> statslist;


    virtual void print() const 
    {
        cout << "Block\t - " << this << " - (total " << statslist->size() << " statements)" << endl;
        for(NStatsList::iterator i=statslist->begin();i!=statslist->end();i++)
        {
            
            cout << "--------------------------------------" << endl;
            (*i)->print();
        }
    }

};













