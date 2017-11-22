#include "codegen_visitor.h"
#include <iostream>

CodegenVisitor::CodegenVisitor(const std::string& filename): Builder{TheContext}, output{filename, EC, llvm::sys::fs::F_None}
{
    TheModule = llvm::make_unique<llvm::Module>("my cool jit", TheContext);
    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();
    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
    if (!Target) {
        llvm::errs() << Error;
    }

    auto CPU = "generic";
    auto Features = "";
    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    targetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    TheModule->setDataLayout(targetMachine->createDataLayout());
    TheModule->setTargetTriple(TargetTriple);
}

void CodegenVisitor::generate()
{
    llvm::legacy::PassManager pass;
    auto FileType = llvm::TargetMachine::CGFT_ObjectFile;
    
    targetMachine->addPassesToEmitFile(pass, output, FileType);
    
    pass.run(*TheModule);

    TheModule->print(llvm::errs(), nullptr);
    output.flush();
}

void CodegenVisitor::visit(Prototype& p)
{
    last_params.clear();
    // Generate types of arguments
    std::vector<llvm::Type*> arg_types(p.getArgs().size(), llvm::Type::getInt32Ty(TheContext));

    // llvm::FunctionType *ft = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), arg_types, false);
    llvm::FunctionType *ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), arg_types, false);
    last_function = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, p.getName(), TheModule.get());
    unsigned Idx = 0;
    for (auto &Arg : last_function->args()) {
        std::string name = ((Argument *) p.getArgs()[Idx++])->getName();
        Arg.setName(name);
        last_params[name] = &Arg;
    }
}

void CodegenVisitor::visit(Argument& node) 
{

}
void CodegenVisitor::visit(Array& node) {}
void CodegenVisitor::visit(ArrayDecl& node) {}
void CodegenVisitor::visit(Assignment& node) {}
void CodegenVisitor::visit(Binary& node) 
{
    node.getLHS()->accept(*this);
    auto L = last_constant;
    node.getRHS()->accept(*this);
    auto R = last_constant;

    switch (node.getOpchar()) {
    case '+':
        last_constant = Builder.CreateAdd(L, R, "tmp");
        break;
    case '-':
        last_constant = Builder.CreateSub(L, R, "tmp");
        break;
    case '*':
        last_constant = Builder.CreateMul(L, R, "tmp");
        break;
    case '/':
        last_constant = Builder.CreateSDiv(L, R, "tmp");
        break;
    }
}
void CodegenVisitor::visit(Boolean& node) {}
// void CodegenVisitor::visit(Factor& node) {}
void CodegenVisitor::visit(For& node) {}
void CodegenVisitor::visit(If& node) {}
void CodegenVisitor::visit(Integer& node) 
{
    last_constant = llvm::ConstantInt::get(TheContext, llvm::APInt(32, node.getValue(), true));
}

void CodegenVisitor::visit(Real& node) 
{
    last_constant = llvm::ConstantFP::get(TheContext, llvm::APFloat(node.getValue()));
}
void CodegenVisitor::visit(RecordDecl& node) {}

// void CodegenVisitor::visit(Relation& node) {}

void CodegenVisitor::visit(Routine& node) 
{
    visit(*node.getPrototype());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", last_function);
    Builder.SetInsertPoint(BB);
    
    verifyFunction(*last_function);
    if (node.getBody()) {
        node.getBody()->accept(*this);
    }
}

void CodegenVisitor::visit(RoutineCall& node) 
{
    llvm::Function *f = TheModule->getFunction(node.getCallee());
    if (!f) {
        std::cout << "no function\n";
    }
    std::vector<llvm::Value*> ArgsV;
    auto& args = node.getArgs();
    for (auto& arg : args) {
        arg->accept(*this);
        ArgsV.push_back(last_constant);
    }

    last_constant = Builder.CreateCall(f, ArgsV, "call");
}
// void CodegenVisitor::visit(Sign& node) {}
// void CodegenVisitor::visit(Type& node) {}
void CodegenVisitor::visit(TypeDecl& node) {}

void CodegenVisitor::visit(Unary& node) {}

void CodegenVisitor::visit(Var& node) 
{

}

void CodegenVisitor::visit(Variable& node) 
{
    std::string name = ((Argument*) node.getVar())->getName();
    last_constant = last_params[name];
}

void CodegenVisitor::visit(Return& node) {
    node.getExpression()->accept(*this);
    Builder.CreateRet(last_constant);
}

void CodegenVisitor::visit(While& node) {

}
