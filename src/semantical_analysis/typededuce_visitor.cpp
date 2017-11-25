#include "typededuce_visitor.h"
#include <iostream>

void TypeDeduceVisitor::visit(Prototype& node) 
{
    std::cout << "Visiting PrototypeNode: " << node.getName();
}
void TypeDeduceVisitor::visit(ArrayDecl& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Assignment& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Binary& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Boolean& node)
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(BooleanType& node)
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Cast& node)
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(For& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(If& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Integer& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(IntegerType& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Real& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(RealType& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(RecordDecl& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Routine& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(RoutineCall& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(TypeDecl& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Unary& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Undefined& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Var& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(Variable& node) 
{
    std::cout << "Foo";
}
void TypeDeduceVisitor::visit(While& node) 
{
    std::cout << "Foo";
}