#include "codegen_visitor.h"
#include <iostream>

void CodegenVisitor::visit(Prototype& p)
{
    std::cout << "visiting " << p.getName() << "\n";
}
