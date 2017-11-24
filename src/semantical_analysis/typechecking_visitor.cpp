#include "typechecking_visitor.h"
#include <iostream>

void TypeCheckingVisitor::visit(Prototype& node) 
{
    std::cout << "Visiting PrototypeNode: " << node.getName();
}
void TypeCheckingVisitor::visit(Argument& node) 
{
    std::cout << "Visiting ArgumentNode: ";
}
void TypeCheckingVisitor::visit(ArrayDecl& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Assignment& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Binary& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Boolean& node)
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(BooleanType& node)
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Cast& node)
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(For& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(If& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Integer& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(IntegerType& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Real& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(RealType& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(RecordDecl& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Routine& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(RoutineCall& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(TypeDecl& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Unary& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Undefined& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Var& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Variable& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(While& node) 
{
    std::cout << "Foo";
}

void TypeCheckingVisitor::visit(Return& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(RecordRef& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(ArrayRef& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Program& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Statements& node) 
{
    std::cout << "Foo";
}
void TypeCheckingVisitor::visit(Void& node) 
{
    std::cout << "Foo";
}