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
#include "lib/cxxopts.hpp"
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
        cxxopts::Options options(argv[0]);
        options
            .positional_help("input")
            .show_positional_help();
        options.add_options()
            ("h,help", "print help")
            ("o,output", "output file", cxxopts::value<std::string>())
            ("i,input", "input file", cxxopts::value<std::string>());
        options.parse_positional("input");

        auto result = options.parse(argc, argv);

        this->error = false;

        this->printHelp = result.count("help");
        this->helpText = options.help();
        if (this->printHelp) {
            return;
        }

        if (!result.count("input")) {
            this->error = true;
            return;
        }
        this->input = result["input"].as<std::string>();

        if (!result.count("output")) {
            this->error = true;
            return;
        }
        this->output = result["output"].as<std::string>();
    }
};

int main(int argc, char *argv[]) {

    CmdArgsParser args(argc, argv);
    if (args.error || args.printHelp) {
        std::cout << args.helpText << std::endl;
        return 0;
    }

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

    // CodegenVisitor v;
    // Prototype p{"hello", std::vector<ASTNode*>{}};
    // v.visit(p);
    std::ifstream fs(args.input);
    Lexer lexer(&fs);
    Parser parser(&lexer);
    auto program = parser.parse();

    return 0;
}
