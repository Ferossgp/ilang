#include <iostream>
#include <fstream>
#include <string>
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
#include "AST/ast.h"
#include "codegen/codegen_visitor.h"
#include "semantical_analysis/semantic_visitor.h"
#include "lib/argparse.hpp"
#include "parsing/Lexer.h"
#include "parsing/Parser.h"

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::unique_ptr<llvm::Module> TheModule;

llvm::Function *codegen_example()
{
    using namespace llvm;
    FunctionType *ft = FunctionType::get(llvm::Type::getVoidTy(TheContext), false);
    auto name = "empty_function";
    Function *f = Function::Create(ft, Function::ExternalLinkage, name, TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
    Builder.SetInsertPoint(BB);
    Builder.CreateRetVoid();
    verifyFunction(*f);

    return f;
}

class CmdArgsParser {
public:
    std::string input;
    std::string output;

    bool printHelp;
    std::string helpText;

    bool error;

public:
    CmdArgsParser(int argc, char *argv[]) {
        ArgumentParser parser;
        parser.useExceptions(true);
        parser.appName(argv[0]);
        parser.addArgument("-h", "--help");
        parser.addArgument("-o", "--output", 1);
        parser.addFinalArgument("input");

        this->helpText = parser.usage();

        this->error = true;
        try {
            parser.parse(argc, (const char**)argv);
        }
        catch (std::exception &e) {
            return;
        }

        this->error = false;

        this->printHelp = parser.count("help");
        if (this->printHelp) {
            return;
        }

        if (!parser.count("input")) {
            this->error = true;
            return;
        }
        this->input = parser.retrieve<std::string>("input");

        if (!parser.count("output")) {
            this->error = true;
            return;
        }
        this->output = parser.retrieve<std::string>("output");
    }
};

int main(int argc, char *argv[]) 
{

    return 0;
}
