#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

using namespace std;

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

class Node {
public:
    virtual ~Node() {}
    virtual llvm::Value* codeGen() { }
    virtual void print() = 0;
};

class NExpression : public Node {
public:
    void print()
    {
        cout << "normal expression" << endl;
    }
};

class NStatement : public Node {
public:
    void print()
    {
        cout << "normal statement" << endl;
    }
};

class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) { }
    llvm::Value* codeGen();
    void print()
    {
        cout << "NInt\t(" << this << ")" << " : " << value << endl;
    }
};

class NDouble : public NExpression {
public:
    double value;
    NDouble(double value) : value(value) { }
    llvm::Value* codeGen();
    void print()
    {
        cout << "NDouble\t(" << this << ")" << " : " << value << endl;
    }
    
};

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    llvm::Value* codeGen();


    void print()
    {
        cout << "NIdent\t(" << this << ")" << " : " << name << endl;
    }
};

class NMethodCall : public NExpression {
public:
    NIdentifier& id;
    ExpressionList arguments;
    NMethodCall(NIdentifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    NMethodCall(NIdentifier& id) : id(id) { }
    llvm::Value* codeGen();

    void print()
    {
        cout << "MethCal\t(" << this << ")" << " : " << "id=" << &id << ", argslist=" << &arguments << endl;
        id.print();
        // for(auto it=arguments.begin();it!=arguments.end();++it)
        // {
        //     (*it)->print();
        // }
    }

};

class NBinaryOperator : public NExpression {
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    llvm::Value* codeGen();


    void print()
    {
        cout << "NBinaryOperator : lhs=" << &lhs << " " << op << " " << &rhs << endl;

        lhs.print();
        rhs.print();
    }
};

class NAssignment : public NExpression {
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignment(NIdentifier& lhs, NExpression& rhs) : 
        lhs(lhs), rhs(rhs) { }
    llvm::Value* codeGen();

    void print()
    {
        cout << "NAssign\t(" << this << ") ident="  << &lhs << ", expr=" << & rhs << endl;
        lhs.print();
        rhs.print();
    }

};


class NBlock : public NExpression {
public:
    StatementList statements;
    NBlock() { }
    virtual llvm::Value* codeGen();

    void print()
    {
        cout << "statement count = " << statements.size() << endl;
        for(auto it = statements.begin();it!=statements.end();it++)
        {
            (*it)->print();
        }
    }
};

class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) : 
        expression(expression) { }
    llvm::Value* codeGen();
    void print()
    {
        cout << "expression statement" << endl;
        expression.print();
    }
};

class NVariableDeclaration : public NStatement {
public:
    const NIdentifier& type;
    NIdentifier& id;
    NExpression *assignmentExpr;
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
        type(type), id(id) { }
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
    llvm::Value* codeGen();

    void print()
    {
        cout << "variable declaration" << endl;
    }
};


class NStringDeclaration : public NStatement {

public:
    NIdentifier & id;
    string & str;

    NStringDeclaration(NIdentifier & id, string & str) : id(id), str(str) {}

    // NStringDeclaration/*  */

    llvm::Value * codeGen();

    void print()
    {
        cout << "String " << id.name << " : " << str << endl;
    }

};


class NFunctionDeclaration : public NStatement {
public:
    const NIdentifier& type;
    const NIdentifier& id;
    VariableList arguments;
    NBlock& block;
    NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, 
            const VariableList& arguments, NBlock& block) :
        type(type), id(id), arguments(arguments), block(block) { }
    llvm::Value* codeGen();

    void print()
    {
        cout << "function declaration" << endl;
    }

};


class ReturnStatement : public NStatement 
{
public: 
    NExpression & retExpr;

    ReturnStatement(NExpression & retExpr) : retExpr(retExpr)
    {}

    llvm::Value * codeGen();

    void print()
    {
        cout << "Return Statement" << endl;
    }

};


