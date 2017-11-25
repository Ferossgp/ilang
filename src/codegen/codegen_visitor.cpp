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
    std::cout << "Generating Object Code\n";
    pass.run(*TheModule);
    std::cout << "Printing IR\n";
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
        auto arg = (Var *) p.args[i];
        switch (arg->var_decl.second->type) {
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

    // function type generation
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


}

void CodegenVisitor::visit(ArrayDecl& node)
{
    std::cout << "Generating ArrayDecl\n";
}

void CodegenVisitor::visit(Assignment& node)
{
    std::cout << "Generating Assignment\n";
    if (!node.value) {
        std::cout << "No right side\n";
    }
    node.value->accept(*this);
    auto name = ((Var *) node.variable)->var_decl.first;
    Builder.CreateStore(last_constant, last_params[name]);
    std::cout << "Assignment generated\n";
}

void CodegenVisitor::visit(Binary& node)
{
    std::cout << "Parsing Binary\n";
    node.type->type = types::Integer;
    node.lhs->accept(*this);
    auto L = last_constant;
    node.rhs->accept(*this);
    auto R = last_constant;

    switch (node.opchar) {
    case opchars::PLUS:
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateAdd(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFAdd(L, R, "tmp");
        }
        break;
    case opchars::MINUS:
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateSub(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFSub(L, R, "tmp");
        }
        break;
    case opchars::MUL:
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateMul(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFMul(L, R, "tmp");
        }
        break;
    case opchars::DIV:
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateSDiv(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFDiv(L, R, "tmp");
        }
        break;
    case opchars::MOD:
        if (node.type->type == types::Integer) {
            last_constant = Builder.CreateSRem(L, R, "tmp");
        } else if (node.type->type == types::Real){
            last_constant = Builder.CreateFRem(L, R, "tmp");
        }
        break;
    case opchars::NOTEQ:
        last_constant = Builder.CreateICmpNE(L, R, "cond");
    }
}

void CodegenVisitor::visit(Boolean& node)
{
    last_constant = llvm::ConstantInt::get(TheContext, llvm::APInt(1, node.value ? 1 : 0, false));
}
void CodegenVisitor::visit(BooleanType& node)
{
    std::cout << "Generating BooleanType\n";
}

void CodegenVisitor::visit(For& node)
{
    std::cout << "Generating For loop\n";
}

void CodegenVisitor::visit(If& node)
{
    std::cout << "Generating If Statement\n";
}

void CodegenVisitor::visit(Integer& node)
{
    std::cout << "Generating Integer\n";
    last_constant = llvm::ConstantInt::get(TheContext, llvm::APInt(32, node.value, true));
}

void CodegenVisitor::visit(IntegerType& node)
{
    std::cout << "Generating Integer Type\n";
}

void CodegenVisitor::visit(Real& node)
{
    last_constant = llvm::ConstantFP::get(TheContext, llvm::APFloat(node.value));
}

void CodegenVisitor::visit(RealType& node)
{
    std::cout << "Generating Real Type\n";
}
void CodegenVisitor::visit(RecordDecl& node)
{
    std::cout << "Generating Record Declaration\n";
}

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
    // arguments generation
    unsigned Idx = 0;
    for (auto &Arg : last_function->args()) {
        std::string name = ((Var *) node.proto->args[Idx++])->var_decl.first;
        auto v = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext), 0, name);
        Builder.CreateStore(&Arg, v);
        Arg.setName(name);
        last_params[name] = v;
    }

    if (node.body->statements.size() > 0) {
        std::cout << "Creating function body\n";
        node.body->accept(*this);
        std::cout << "Created function body\n";
        if (last_function->getReturnType() == llvm::Type::getVoidTy(TheContext)) {
            Builder.CreateRetVoid();
            return;
        }
    } else {
        std::cout << "Creating Return void\n";
        Builder.CreateRetVoid();
    }

    verifyFunction(*last_function);
}

void CodegenVisitor::visit(RoutineCall& node)
{
    std::cout << "Parsing call to" << node.callee << "\n";
    llvm::Function *f = TheModule->getFunction(node.callee->proto->name);
    if (!f) {
        std::cout << "no function\n";
    }
    std::vector<llvm::Value*> ArgsV;
    for (auto& arg : node.args) {
        arg->accept(*this);
        ArgsV.push_back(last_constant);
    }

    last_constant = Builder.CreateCall(f, ArgsV, "call");
}

void CodegenVisitor::visit(TypeDecl& node)
{
    std::cout << "Generating Type Decl\n";
}

void CodegenVisitor::visit(Unary& node)
{
    std::cout << "Generating Unary ";
    std::cout << node.opcode << "\n";

}

void CodegenVisitor::visit(Var& node)
{
    std::cout << "Creating Var declaration\n";
    auto name = node.var_decl.first;
    auto v = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext), 0, name);
    if (node.body) {
        node.body->accept(*this);
        Builder.CreateStore(last_constant, v);
    }
    last_params[name] = v;
    std::cout << "Created Var declaration\n";
}

void CodegenVisitor::visit(Variable& node)
{
    std::cout << "Parsing Variable\n";
    if (!node.var ) {
        std::cout << "var is 0\n";
    }
    std::string name = node.var->var_decl.first;
    auto value = last_params[name];
    last_constant = Builder.CreateLoad(value, name.c_str());
}

void CodegenVisitor::visit(Return& node) {
    std::cout << "Parsing Return\n";
    node.expression->accept(*this);
    Builder.CreateRet(last_constant);
}

void CodegenVisitor::visit(While& node) {
    std::cout << "Generating While loop\n";
    auto cond = llvm::BasicBlock::Create(TheContext, "loopcond");
    auto loop = llvm::BasicBlock::Create(TheContext, "loop");
    last_function->getBasicBlockList().push_back(cond);
    auto end = llvm::BasicBlock::Create(TheContext, "loopend");
    Builder.CreateBr(cond);
    Builder.SetInsertPoint(cond);

    // insert condition
    node.expression->accept(*this);
    Builder.CreateCondBr(last_constant, loop, end);
    // //
    last_function->getBasicBlockList().push_back(loop);
    Builder.SetInsertPoint(loop);
    node.body->accept(*this);
    Builder.CreateBr(cond);
    last_function->getBasicBlockList().push_back(end);
    Builder.SetInsertPoint(end);
}

void CodegenVisitor::visit(RecordRef& node) {
    std::cout << "Generating Record Reference\n";
}

void CodegenVisitor::visit(ArrayRef& node) {
    std::cout << "Generating ArrayRef\n";
}

void CodegenVisitor::visit(Program& node) {
    std::cout << "Generating Program\n";
    for (auto& n : node.program) {
        n->accept(*this);
    }
    std::cout << "Program Generated\n";
}

void CodegenVisitor::visit(Statements& node) {
    std::cout << "parsing statements\n";
    for (auto& n : node.statements) {
        if (!n) {
            std::cout << "Node is nullptr\n";
        }
        n->accept(*this);
    }
    std::cout << "Statements generated\n";
}

void CodegenVisitor::visit(Void& node) {
    std::cout << "Generating Void\n";
}

void CodegenVisitor::visit(Undefined& node) {
    std::cout << "Generating Undefined\n";
}

void CodegenVisitor::visit(Cast& node)
{
    std::cout << "Generating Cast\n";
}
