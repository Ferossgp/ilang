#include <memory>

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

#include "../visitor.h"
#include "../AST/prototype.h"
#include "../AST/argument.h"
#include "../AST/integer.h"
#include "../AST/real.h"
#include "../AST/routine.h"
#include "../AST/binary.h"

// using namespace llvm;

class CodegenVisitor : Visitor
{
private:
    llvm::LLVMContext TheContext;
    llvm::IRBuilder<> Builder;
    std::unique_ptr<llvm::Module> TheModule;
    llvm::TargetMachine* targetMachine;
    llvm::raw_fd_ostream output;
    std::error_code EC;

    llvm::Value *last_constant;    
    llvm::Function *last_function;

public:
    CodegenVisitor(const std::string& filename);
    CodegenVisitor() = delete;
    void visit(Prototype& p);
    void visit(Argument& node);
    void visit(Array& node);
    void visit(ArrayDecl& node);
    void visit(Assignment& node);
    void visit(Binary& node);
    void visit(Boolean& node);
    // void visit(Factor& node);
    void visit(For& node);
    void visit(If& node);
    void visit(Integer& node);
    void visit(Real& node);
    void visit(RecordDecl& node);
    // void visit(Relation& node);
    void visit(Routine& node);
    void visit(RoutineCall& node);
    // void visit(Sign& node);
    // void visit(Type& node);
    void visit(TypeDecl& node);
    void visit(Unary& node);
    void visit(Var& node);
    void visit(Variable& node);
    void visit(While& node);
    void generate();
};
