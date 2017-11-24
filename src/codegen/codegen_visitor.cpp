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
    std::cout << "Parsing Prototype\n";
    last_params.clear();
    // Generate types of arguments
    std::vector<llvm::Type*> arg_types{};
    for (int i =0; i < p.args.size(); i++) {
        auto arg = (Argument *) p.args[i];
        switch (arg->arg_decl.second->type) {
        case types::Integer:
            arg_types.push_back(llvm::Type::getInt32Ty(TheContext));
            break;
        case types::Real:
            arg_types.push_back(llvm::Type::getDoubleTy(TheContext));
            break;
        case types::Boolean:
            arg_types.push_back(llvm::Type::getInt1Ty(TheContext));
            break;
        }
    }

    llvm::FunctionType *ft;
    switch (p.type->type) {
    case types::Integer:
        ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), arg_types, false);
        break;
    case types::Void:
        ft = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), arg_types, false);
        break;
    case types::Real:
        ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(TheContext), arg_types, false);
        break;
    case types::Boolean:
        ft = llvm::FunctionType::get(llvm::Type::getInt1Ty(TheContext), arg_types, false);
        break;
    }
    last_function = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, p.getName(), TheModule.get());

    unsigned Idx = 0;
    for (auto &Arg : last_function->args()) {
        std::string name = ((Argument *) p.args[Idx++])->arg_decl.first;
        Arg.setName(name);
        last_params[name] = &Arg;
    }
}

void CodegenVisitor::visit(Argument& node)
{

}

void CodegenVisitor::visit(ArrayDecl& node) {}

void CodegenVisitor::visit(Assignment& node) {}

void CodegenVisitor::visit(Binary& node)
{
    std::cout << "Parsing Binary\n";
    node.lhs->accept(*this);
    auto L = last_constant;
    node.rhs->accept(*this);
    auto R = last_constant;

    switch (node.opchar) {
    case '+':
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateAdd(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFAdd(L, R, "tmp");
        }
        break;
    case '-':
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateSub(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFSub(L, R, "tmp");
        }
        break;
    case '*':
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateMul(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFMul(L, R, "tmp");
        }
        break;
    case '/':
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateSDiv(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFDiv(L, R, "tmp");
        }
        break;
    case '%':
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateSRem(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFRem(L, R, "tmp");
        }
        break;
    }
}
void CodegenVisitor::visit(Boolean& node)
{
    last_constant = llvm::ConstantInt::get(TheContext, llvm::APInt(1, node.value ? 1 : 0, false));
}
void CodegenVisitor::visit(BooleanType& node) {}

void CodegenVisitor::visit(For& node) {}
void CodegenVisitor::visit(If& node) {}
void CodegenVisitor::visit(Integer& node)
{
    last_constant = llvm::ConstantInt::get(TheContext, llvm::APInt(32, node.value, true));
}

void CodegenVisitor::visit(IntegerType& node) {}

void CodegenVisitor::visit(Real& node)
{
    last_constant = llvm::ConstantFP::get(TheContext, llvm::APFloat(node.value));
}

void CodegenVisitor::visit(RealType& node) {}
void CodegenVisitor::visit(RecordDecl& node) {}

void CodegenVisitor::visit(Routine& node)
{
    std::cout << "Parsing routine\n";
    node.proto->accept(*this);
    std::cout << "Parsed Prototype\n";

    if (!last_function) {
        std::cout << "No last function\n";
    }
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", last_function);
    Builder.SetInsertPoint(BB);
    std::cout << "Basic Block Created\n";
    if (node.body->statements.size() > 0) {
        std::cout << "Creating function body\n";
        node.body->accept(*this);
    } else {
        std::cout << "Creating Return void\n";
        Builder.CreateRetVoid();
    }

    verifyFunction(*last_function);
}

void CodegenVisitor::visit(RoutineCall& node)
{
    // llvm::Function *f = TheModule->getFunction(node.getCallee());
    // if (!f) {
    //     std::cout << "no function\n";
    // }
    // std::vector<llvm::Value*> ArgsV;
    // auto& args = node.getArgs();
    // for (auto& arg : args) {
    //     arg->accept(*this);
    //     ArgsV.push_back(last_constant);
    // }

    // last_constant = Builder.CreateCall(f, ArgsV, "call");
}

void CodegenVisitor::visit(TypeDecl& node) {}

void CodegenVisitor::visit(Unary& node) {}

void CodegenVisitor::visit(Var& node)
{

}

void CodegenVisitor::visit(Variable& node)
{
    std::cout << "Parsing Variable\n";
    if (!node.var ) {
        std::cout << "var is 0\n";
    }
    std::string name = ((Argument*) node.var)->arg_decl.first;
    last_constant = last_params[name];
}

void CodegenVisitor::visit(Return& node) {
    std::cout << "Parsing Return\n";
    node.expression->accept(*this);
    Builder.CreateRet(last_constant);

}

void CodegenVisitor::visit(While& node) {

}

void CodegenVisitor::visit(RecordRef& node) {

}

void CodegenVisitor::visit(ArrayRef& node) {

}

void CodegenVisitor::visit(Program& node) {
    for (auto& n : node.program) {
        n->accept(*this);
    }
}

void CodegenVisitor::visit(Statements& node) {
    std::cout << "parsing statements\n";
    for (auto& n : node.statements) {
        if (!n) {
            std::cout << "Node is nullptr\n";
        }
        n->accept(*this);
    }
}

void CodegenVisitor::visit(Void& node) {

}

void CodegenVisitor::visit(Undefined& node) {

}
