#include <iostream>
#include "llvm/IR/LLVMContext.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "ast.h"

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);

int main() {
    auto TheModule = llvm::make_unique<llvm::Module>("my cool jit", TheContext);
    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    TheModule->setTargetTriple(TargetTriple);
}
