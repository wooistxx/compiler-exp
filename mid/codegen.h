#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Constants.h>
// #include <llvm/IR/PassManager.h>
// #include <llvm/Support/raw_ostream.h>
// #include <llvm/Instructions.h>
// #include <llvm/CallingConv.h>
// #include <llvm/Bitcode/ReaderWriter.h>
// #include <llvm/Analysis/Verifier.h>
// #include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
// #include <llvm/ModuleProvider.h>
// #include <llvm/Target/TargetSelect.h>
//#include <llvm/ExecutionEngine/GenericValue.h>
// #include <llvm/ExecutionEngine/JIT.h>


using namespace llvm;

class NBlock;


extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder; 
extern llvm::Module * TheModule;
extern std::map<std::string, Value *> NamedValues;



class CodeGenBlock {
// public:
//     BasicBlock *block;
//     std::map<std::string, Value*> locals;
};

// class CodeGenContext {
// //     std::stack<CodeGenBlock *> blocks;
// //     Function * mainFunction;

// public:
//     Module * module;
//     CodeGenContext() { module = new Module("main", TheContext); }
    
//     void generateCode(NBlock& root);
// //     // GenericValue runCode();
// //     std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
// //     BasicBlock *currentBlock() { return blocks.top()->block; }
// //     void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
// //     void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
// };




void createSystemFunc();
