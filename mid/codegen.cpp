#include "node.h"
#include "codegen.h"
#include "parser.hpp"

using namespace std;




/* Compile the AST into a module */
// void CodeGenContext::generateCode(NBlock& root)
// {
//     // //  创建一个 main 函数作为函数的入口
//     // FunctionType * mainftype = FunctionType::get(Type::getVoidTy(context), {}, false);
//     // mainFunction = Function::Create(mainftype, GlobalValue::InternalLinkage, "main", module);
//     // BasicBlock *bblock = BasicBlock::Create(context, "entrypoint", mainFunction /*, 0*/ );

//     // cout << "Generating code..." << endl;;


//     // // /* Push a new variable/block context
//     // pushBlock(bblock);

//     // root.codeGen(*this); /* emit bytecode for the toplevel block */

//     // ReturnInst::Create(/*getGlobalContext()*/ context, bblock);
//     // popBlock();
    
//     // // /* Print the bytecode in a human-readable format 
//     //    to see if our program compiled properly
//     //  */
//     // std::cout << "Code is generated.n";
// //     legacy::PassManager passManager;
// //     passManager.add(createPrintModulePass(&outs()));
// //     // passManager.run(*(this->theModule.get()));
// // //     pm.add(createPrintModulePass(&outs()));
// //     passManager.run(*module);

// }

// Executes the AST by running the main function 
// GenericValue CodeGenContext::runCode() 
// {
    // std::cout << "Running code...n";
    // ExistingModuleProvider *mp = new ExistingModuleProvider(module);
    // ExecutionEngine *ee = ExecutionEngine::create(mp, false);
    // vector<GenericValue> noargs;
    // GenericValue v = ee->runFunction(mainFunction, noargs);
    // std::cout << "Code was run.n";
    // return v;
// }

// Returns an LLVM type based on the identifier 
static Type * typeOf(const NIdentifier& type) 
{
    if (type.name.compare("int") == 0)
    {
        return Type::getInt32Ty(TheContext);
    }
    else if (type.name.compare("double") == 0)
    {
        return Type::getDoubleTy(TheContext);
    }
    else
        return Type::getVoidTy(TheContext);
}

/* -- Code Generation -- */

Value* NInteger::codeGen()
{
    // std::cout << "Creating integer: " << value << std::endl;
    // return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value, true);
    std::cout << "NInteger::codeGen" << std::endl;
    return llvm::ConstantInt::get(TheContext, llvm::APInt(32, value));
}


Value* NDouble::codeGen()
{
    std::cout << "NDouble::codeGen" << std::endl;
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
}


Value* NIdentifier::codeGen()
{
    // std::cout << "Creating identifier reference: " << name << std::endl;
    // if (context.locals().find(name) == context.locals().end()) {
    //     std::cerr << "undeclared variable " << name << std::endl;
    //     return NULL;
    // }
    // return new LoadInst(context.locals()[name], "", false, context.currentBlock());
    
    /*
        cout << "Generating identifier " << this->name << endl;
        Value* value = context.getSymbolValue(this->name);
        if( !value ){
            return LogErrorV("Unknown variable name " + this->name);
        }
        if( value->getType()->isPointerTy() ){
            auto arrayPtr = context.builder.CreateLoad(value, "arrayPtr");
            if( arrayPtr->getType()->isArrayTy() ){
                cout << "(Array Type)" << endl;
    //            arrayPtr->setAlignment(16);
                std::vector<Value*> indices;
                indices.push_back(ConstantInt::get(context.typeSystem.intTy, 0, false));
                auto ptr = context.builder.CreateInBoundsGEP(value, indices, "arrayPtr");
                return ptr;
            }
        }
        return context.builder.CreateLoad(value, false, "");
    */


    return NamedValues[name];

    // Value * v = Builder.CreateLoad( /*Builder.getInt8PtrTy(), */ NamedValues[name]);
    // return v;

    //return Builder.CreateLoad(NamedValues[name]);
    /* https://my.oschina.net/linlifeng/blog/97457

        Value* IdentExpr::codeGen(AstContext &astContext){
            Value *var = astContext.getVar(ident);
            if(var == NULL){
                throwError(this);
            }
            return builder.CreateLoad(var);
        }
    */

}


Value* NMethodCall::codeGen()
{
    // Function *function = context.module->getFunction(id.name.c_str());
    // if (function == NULL) {
    //     std::cerr << "no such function " << id.name << std::endl;
    // }
    // std::vector<Value*> args;
    // ExpressionList::const_iterator it;
    // for (it = arguments.begin(); it != arguments.end(); it++) {
    //     args.push_back((**it).codeGen(context));
    // }
    // CallInst *call = CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
    std::cout << "NMethodCall::codeGen" << std::endl;
    Function * CalleeF = TheModule->getFunction(id.name);
    // if (!CalleeF)
    //     return LogErrorV("Unknown function referenced");

    // // If argument mismatch error.
    // if (CalleeF->arg_size() != Args.size())
    //     return LogErrorV("Incorrect # arguments passed");

    // return Builder.CreateCall(CalleeF, { arguments[0]->codeGen() });

    std::vector<Value *> ArgsV;
    for (unsigned i = 0, e = arguments.size(); i != e; ++i) {
        ArgsV.push_back(arguments[i]->codeGen());
        // if (!ArgsV.back())
        // return nullptr;
    }
    // return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
    return Builder.CreateCall(CalleeF, ArgsV);

}

Value* NBinaryOperator::codeGen()
{
    std::cout << "Creating binary operation " << op << std::endl;
    // Instruction::BinaryOps instr;

  
    Value * L = // llvm::ConstantInt::get(TheContext, llvm::APInt(32, 3)); 
    lhs.codeGen();
    Value * R = //llvm::ConstantInt::get(TheContext, llvm::APInt(32, 3)); 
    rhs.codeGen();


    // https://www.killf.info/%E5%85%B6%E4%BB%96%E5%86%85%E5%AE%B9/LLVM%E5%85%A5%E9%97%A8%E7%B3%BB%E5%88%97%E4%B9%8B%E5%B1%80%E9%83%A8%E5%8F%98%E9%87%8F%E5%92%8C%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F/

    // https://blog.csdn.net/weixin_33843947/article/details/92060755

    
    // //申请栈空间，并返回对应的指针
    // llvm::AllocaInst *variable = Builder.CreateAlloca(Builder.getInt32Ty());
    // //将值存储到指定的位置
    // Builder.CreateStore(Builder.getInt32(1024), variable);
    // //加在指定位置处的值
    // // Builder.CreateRet(Builder.CreateLoad(variable));

    if(!L || !R)
        return nullptr;

    switch (op)
    {
        case TPLUS:
            return Builder.CreateAdd(L, R, "addtmp");
        case TMINUS:
            return Builder.CreateSub(L, R, "subtmp");
        case TMUL:
            return Builder.CreateMul(L, R, "multmp");
        case TDIV:
            return Builder.CreateSDiv(L, R, "divtmp");
        /*
        https://stackoverflow.com/questions/5346160/llvm-irbuildercreateudiv-createsdiv-createexactudiv

        I assume LLVM uses two's complement to store integers and in that case a (signed) negative number will seem like a large unsigned number for UDiv, (e.g. the two's complement representation for 32-bit -1 is 0xFFFFFFFF). Thus SDiv(-16, 2) == -8 while UDiv(-16, 2) == 2147483640.
        */

        default:
            return nullptr;

    }
// math:
//     cout << "..............." << endl;
//     return BinaryOperator::Create(instr, lhs.codeGen(context), 
//         rhs.codeGen(context), "", context.currentBlock());
}

Value* NAssignment::codeGen()
{
    std::cout << "NAssignment::codeGen" << std::endl;
    // std::cout << "Creating assignment for " << lhs.name << std::endl;
    // if (context.locals().find(lhs.name) == context.locals().end()) {
    //     std::cerr << "undeclared variable " << lhs.name << std::endl;
    //     return NULL;
    // }
    // return new StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
    return nullptr;
}

Value* NBlock::codeGen()
{
    std::cout << "Creating block" << std::endl;
    StatementList::const_iterator it;
    Value *last = NULL;
    for (it = statements.begin(); it != statements.end(); it++)
    {
        // std::cout << "Generating code for " << typeid(**it).name() << std::endl;
        last = (**it).codeGen();
    }
    return last;
}

Value* NExpressionStatement::codeGen()
{
    // std::cout << "Generating code for " << typeid(expression).name() << std::endl;
    std::cout << "NExpressionStatement::codeGen" << std::endl;
    return expression.codeGen();
}

Value* NVariableDeclaration::codeGen()
{
    std::cout << "Creating variable declaration, type : " << type.name<< std::endl;
    if(type.name == "int")
    {
        llvm::AllocaInst * variable = Builder.CreateAlloca(Builder.getInt32Ty());
        if(assignmentExpr != nullptr)
        {
            Value * vValue = assignmentExpr->codeGen();
            Builder.CreateStore(vValue, variable);
        }
        else
        {
            Builder.CreateStore(Builder.getInt32(0), variable);
        }
        NamedValues[id.name] = variable;
        return variable;
    }
    else if(type.name == "double")
    {

    }
    

    // Value * v = NamedValues[];
    return nullptr;

}


Value * NStringDeclaration::codeGen()
{


    //llvm::AllocaInst * strp = Builder.CreateAlloca(Builder.getInt8PtrTy());
    llvm::Value * strv = Builder.CreateGlobalStringPtr(str);


    // Builder.CreateCall(TheModule->getFunction("printS"), {strv} );
    // 这样是 OK 的


    return NamedValues[id.name] = strv;

}


Value* NFunctionDeclaration::codeGen()
{
    if(id.name == "main")
    {
        llvm::FunctionType * funcType = llvm::FunctionType::get(Builder.getInt32Ty(), false);
        llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", TheModule);
        llvm::BasicBlock * mainEntry = llvm::BasicBlock::Create(TheContext, "entrypoint", mainFunc);
        Builder.SetInsertPoint(mainEntry);
        block.codeGen();
    }
    else
    {


    // Function *TheFunction = TheModule->getFunction(id.name);
    // vector<const Type*> argTypes;
    // VariableList::const_iterator it;
    // for (it = arguments.begin(); it != arguments.end(); it++) {
    //     argTypes.push_back(typeOf((**it).type));
    // }

    /*
    
    如果一个GlobalValue有internal linkage(相当于C语言中的static链接)，那么它对于当前翻译单元之外的代码是不可见的，并且不参与链接。如果它有external linkage，那么它对外部代码是可见的，并且确实参与了链接。除了linkage信息，GlobalValues还跟踪它们当前属于哪个Module。
        原文链接：https://blog.csdn.net/qq_23599965/article/details/88538590
    
    */

   /*
    http://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl03.html#full-code-listing
   */
        vector<Type*> argTypes;
        // VariableList::const_iterator it;
        for (auto it = arguments.begin(); it != arguments.end(); it++) 
        {
            argTypes.push_back(typeOf((**it).type));
        }
        ArrayRef<Type * > argTypesRef(argTypes);
        FunctionType * ftype = FunctionType::get(typeOf(type), argTypesRef, false);

        Function * function = Function::Create(ftype, GlobalValue::InternalLinkage, id.name.c_str(), TheModule);

        unsigned idx = 0;
        for(auto & arg : function->args())
            arg.setName(arguments[idx++]->id.name);

    // Prototype finished, next is the block -----------------------------


        BasicBlock * bblock = BasicBlock::Create(TheContext, "entry", function, 0);

        Builder.SetInsertPoint(bblock);

        // declare function params
        unsigned i = 0;
        for(Function::arg_iterator ai = function->arg_begin();ai != function->arg_end(); ai++,i++){
           // NExpression * argDecl = arguments[i];
            Value *alloc = Builder.CreateAlloca(Type::getInt32Ty(TheContext)/*argTypes[i]*/);
            Builder.CreateStore(ai, alloc);

            NamedValues[ai->getName()] = alloc;
            // if(!newContext.addVar(argDecl->varName,alloc)){
            //     throwError(&argDecl->varName);
            // }
        }





        block.codeGen();

        return function;
        // if (Value *RetVal = block->codegen()) {
        //     // Finish off the function.
        //     Builder.CreateRet(RetVal);

        //     // Validate the generated code, checking for consistency.
        //     verifyFunction(*TheFunction);
        //     return TheFunction;
        // }



    // context.pushBlock(bblock);
    // for (it = arguments.begin(); it != arguments.end(); it++) {
    //     (**it).codeGen(context);
    // }
    // block.codeGen();
    // ReturnInst::Create(getGlobalContext(), bblock);

    // context.popBlock();
    // std::cout << "Creating function: " << id.name << std::endl;
    // return function;
    }

    return nullptr;
}



Value * ReturnStatement::codeGen()
{
    Value * retVal = retExpr.codeGen();
    if(retVal != nullptr)
        Builder.CreateRet(retVal);
    else
    {
        Builder.CreateRetVoid();
    }
}



void createSystemFunc()
{

    // https://my.oschina.net/linlifeng/blog/97457


    //insert printf func decl
	vector<Type*> printfFuncArgTypes;
	printfFuncArgTypes.push_back(Builder.getInt8PtrTy());
	ArrayRef<Type*> printfFuncArgTypesRef(printfFuncArgTypes);
	FunctionType *printfFuncType = FunctionType::get(Builder.getInt32Ty(),printfFuncArgTypesRef,true);
	Constant *printfFunc = TheModule->getOrInsertFunction("printf",printfFuncType);
/*   
        Function * function = Function::Create(ftype, GlobalValue::InternalLinkage, id.name.c_str(), TheModule);
        BasicBlock * bblock = BasicBlock::Create(TheContext, "entry", function, 0);
        Builder.SetInsertPoint(bblock);
        // ===============================================
        Builder.CreateCall(CalleeF, ArgsV, "calltmp");
*/
    vector<Type*> emptyTypes;

    // printI
    vector<Type *> printIntFuncArgTypes;
    printIntFuncArgTypes.push_back(Builder.getInt32Ty());
    ArrayRef<Type *> printIntFuncArgTypesRef(printIntFuncArgTypes);
    FunctionType * printIntFuncType = FunctionType::get(Builder.getVoidTy(), printIntFuncArgTypes, false);
    Function * printIntFunc = Function::Create(printIntFuncType, GlobalValue::InternalLinkage/*, printIntFuncArgTypes*/, "printI", TheModule);
    Builder.SetInsertPoint(BasicBlock::Create(TheContext, "entry", printIntFunc));
    Value * intFormat = Builder.CreateGlobalStringPtr("%d");
    Builder.CreateCall(printfFunc, { intFormat, printIntFunc->arg_begin() });
    Builder.CreateRetVoid();

    // printS
    vector<Type *> printStrFuncArgTypes;
    printStrFuncArgTypes.push_back(Builder.getInt8PtrTy());
    ArrayRef<Type *> printStrFuncArgTypesRef(printStrFuncArgTypes);
    FunctionType * printStrFuncType = FunctionType::get(Builder.getVoidTy(), printStrFuncArgTypes, false);
    Function * printStrFunc = Function::Create(printStrFuncType, GlobalValue::InternalLinkage, "printS", TheModule);
    Builder.SetInsertPoint(BasicBlock::Create(TheContext, "entry", printStrFunc));
    Value * strFormat = Builder.CreateGlobalStringPtr("%s");
    Builder.CreateCall(printfFunc, { strFormat, printStrFunc->arg_begin() });
    Builder.CreateRetVoid();

    /*
    
lli: helloworld.ll:33:13: error: '@printS' defined with type 'void (i8*)*' but expected 'void (i8)*'
  call void @printS(i8 %0)
            ^

    
    */


    // vector<Type*> emptyTypes;
    // //create print long func
	// vector<Type*> printfLongFuncArgTypes;
	// printfLongFuncArgTypes.push_back(builder.getInt64Ty());
	// ArrayRef<Type*> printfLongFuncArgTypesRef(printfLongFuncArgTypes);
	// FunctionType *printfLongFuncType = FunctionType::get(builder.getVoidTy(),printfLongFuncArgTypesRef,false);
	// Function *printfLongFunc = Function::Create(printfLongFuncType,Function::ExternalLinkage,"printL",&module);
	// builder.SetInsertPoint(BasicBlock::Create(context,"entry",printfLongFunc));
	// Value *longFormat = builder.CreateGlobalStringPtr("%ld");
	// builder.CreateCall2(printfFunc,longFormat,printfLongFunc->arg_begin());
	// builder.CreateRetVoid();
	// AstFunction *printfL = new AstFunction("printL",printfLongFunc,emptyTypes,printfLongFuncArgTypes);

	// //create print double func
	// vector<Type*> printfDoubleFuncArgTypes;
	// printfDoubleFuncArgTypes.push_back(builder.getDoubleTy());
	// ArrayRef<Type*> printfDoubleFuncArgTypesRef(printfDoubleFuncArgTypes);
	// FunctionType *printfDoubleFuncType = FunctionType::get(builder.getVoidTy(),printfDoubleFuncArgTypesRef,false);
	// Function *printfDoubleFunc = Function::Create(printfDoubleFuncType,Function::ExternalLinkage,"printD",&module);
	// builder.SetInsertPoint(BasicBlock::Create(context,"entry",printfDoubleFunc));
	// Value *doubleFormat = builder.CreateGlobalStringPtr("%lf");
	// builder.CreateCall2(printfFunc,doubleFormat,printfDoubleFunc->arg_begin());
	// builder.CreateRetVoid();
	// AstFunction *printfD = new AstFunction("printD",printfDoubleFunc,emptyTypes,printfDoubleFuncArgTypes);

	// //create println func
	// FunctionType *printlnFuncType = FunctionType::get(builder.getVoidTy(),false);
	// Function *printlnFunc = Function::Create(printlnFuncType,Function::ExternalLinkage,"println",&module);
	// builder.SetInsertPoint(BasicBlock::Create(context,"entry",printlnFunc));
	// Value *lnFormat = builder.CreateGlobalStringPtr("\n");
	// builder.CreateCall(printfFunc,lnFormat);
	// builder.CreateRetVoid();
	// AstFunction *println = new AstFunction("println",printlnFunc,emptyTypes,emptyTypes);

	//astContext.addFunction("printf",cast<Function>(printfFunc));
	// astContext.addFunction("printL",printfL);
	// astContext.addFunction("printD",printfD);
	// astContext.addFunction("println",println);



}



