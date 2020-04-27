#include <iostream>
#include <string>
#include <map>
#include "codegen.h"
#include "node.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

using namespace std;
using namespace llvm;
extern int yyparse();
extern NBlock * GlobalBlock;
extern FILE * yyin;

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext); 
llvm::Module * TheModule;
std::map<std::string, Value *> NamedValues;

int main(int argc, char **argv)
{
    string fname;
    cin >> fname;
    yyin = fopen(fname.c_str(), "r");

    if(yyin == NULL)
    {
        cout << "file open error!" << endl;
        return -1;
    }
    // -------------------------------------------------

    TheModule = new llvm::Module("global", TheContext);
    yyparse();
    cout << "--------------------------" << endl;
    GlobalBlock->print();

    cout << "--------------------------" << endl;

    createSystemFunc();
    GlobalBlock->codeGen();

    cout << "--------------------------" << endl;
    TheModule->print(outs(), nullptr);
    
    return 0;
}


