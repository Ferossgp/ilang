#include "printname_visitor.h"
#include <iostream>

void PrintNameVisitor::visit(Prototype& node) 
{
    std::cout << "Visiting PrototypeNode: " << node.getName();
}
void PrintNameVisitor::visit(Argument& node) 
{
    std::cout << "Visiting ArgumentNode: ";
}
void PrintNameVisitor::visit(ArrayDecl& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Assignment& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Binary& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Boolean& node)
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(BooleanType& node)
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(For& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(If& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Integer& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(IntegerType& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Real& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(RealType& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(RecordDecl& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Routine& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(RoutineCall& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(TypeDecl& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Unary& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Undefined& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Var& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(Variable& node) 
{
    std::cout << "Foo";
}
void PrintNameVisitor::visit(While& node) 
{
    std::cout << "Foo";
}