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
    output.flush();
}

void CodegenVisitor::visit(Prototype& p)
{
    llvm::FunctionType *ft = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), false);
    llvm::Function *f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, p.getName(), TheModule.get());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", f);
    Builder.SetInsertPoint(BB);
    Builder.CreateRetVoid();
    verifyFunction(*f);
}

void CodegenVisitor::visit(Argument& node) {}
void CodegenVisitor::visit(Array& node) {}
void CodegenVisitor::visit(ArrayDecl& node) {}
void CodegenVisitor::visit(Assignment& node) {}
void CodegenVisitor::visit(Binary& node) {}
void CodegenVisitor::visit(Boolean& node) {}
// void CodegenVisitor::visit(Factor& node) {}
void CodegenVisitor::visit(For& node) {}
void CodegenVisitor::visit(If& node) {}
void CodegenVisitor::visit(Integer& node) {}
void CodegenVisitor::visit(Real& node) {}
void CodegenVisitor::visit(RecordDecl& node) {}
// void CodegenVisitor::visit(Relation& node) {}
void CodegenVisitor::visit(Routine& node) {}
void CodegenVisitor::visit(RoutineCall& node) {}
// void CodegenVisitor::visit(Sign& node) {}
// void CodegenVisitor::visit(Type& node) {}
void CodegenVisitor::visit(TypeDecl& node) {}
void CodegenVisitor::visit(Unary& node) {}
void CodegenVisitor::visit(Var& node) {}
void CodegenVisitor::visit(Variable& node) {}
void CodegenVisitor::visit(While& node) {}
