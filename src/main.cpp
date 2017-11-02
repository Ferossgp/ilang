#include <iostream>
#include <fstream>
#include "llvm/IR/LLVMContext.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/IR/LegacyPassManager.h"
#include "ast.h"

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::unique_ptr<llvm::Module> TheModule;

llvm::Function *codegen_example() 
{
    using namespace llvm;
    FunctionType *ft = FunctionType::get(Type::getVoidTy(TheContext), false);
    auto name = "empty_function";
    Function *f = Function::Create(ft, Function::ExternalLinkage, name, TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
    Builder.SetInsertPoint(BB);
    Builder.CreateRetVoid();
    verifyFunction(*f);

    return f;
}

int main() 
{
    using namespace llvm;
    TheModule = llvm::make_unique<llvm::Module>("my cool jit", TheContext);
    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();
    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
    if (!Target) {
        errs() << Error;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";
    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto targetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    TheModule->setDataLayout(targetMachine->createDataLayout());
    TheModule->setTargetTriple(TargetTriple);

    auto Filename = "empty_function.vocout";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::F_None);
    
    if (EC) {
      errs() << "Could not open file: " << EC.message();
      return 1;
    }
    codegen_example();

    legacy::PassManager pass;
    auto FileType = TargetMachine::CGFT_ObjectFile;
    
    if (targetMachine->addPassesToEmitFile(pass, dest, FileType)) {
      errs() << "TargetMachine can't emit a file of this type";
      return 1;
    }
    
    pass.run(*TheModule);
    dest.flush();

}
