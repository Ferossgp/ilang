#include "printname_visitor.h"
#include <iostream>

void PrintNameVisitor::visit(Prototype& node) 
{
    std::cout << "Visiting PrototypeNode\n";
}
void PrintNameVisitor::visit(ArrayDecl& node) 
{
    std::cout << "Visiting ArrayDecl\n";
    node.array_type->accept(*this);
    node.expression->accept(*this);
}
void PrintNameVisitor::visit(Assignment& node) 
{
    std::cout << "Visiting Assignment\n";
    node.variable->accept(*this);
    node.value->accept(*this);
}
void PrintNameVisitor::visit(Binary& node) 
{
    std::cout << "Visiting Binary\n";
    node.lhs->accept(*this);
    node.rhs->accept(*this);
}
void PrintNameVisitor::visit(Boolean& node)
{
    std::cout << "Visiting Boolean\n";
}
void PrintNameVisitor::visit(BooleanType& node)
{
    std::cout << "Visiting BooleanType\n";
}
void PrintNameVisitor::visit(Cast& node)
{
    std::cout << "Visiting Cast\n";
    node.value->accept(*this);
}
void PrintNameVisitor::visit(For& node) 
{
    std::cout << "Visiting For\n";
    node.body->accept(*this);
}
void PrintNameVisitor::visit(If& node) 
{
    std::cout << "Visiting If\n";
    node.then->accept(*this);
    node.else_body->accept(*this);
}
void PrintNameVisitor::visit(Integer& node) 
{
    std::cout << "Visiting Integer\n";
}
void PrintNameVisitor::visit(IntegerType& node) 
{
    std::cout << "Visiting IntegerType\n";
}
void PrintNameVisitor::visit(Real& node) 
{
    std::cout << "Visiting Real\n";
}
void PrintNameVisitor::visit(RealType& node) 
{
    std::cout << "Visiting RealType\n";
}
void PrintNameVisitor::visit(RecordDecl& node) 
{
    std::cout << "Visiting RecordDecl\n";
}
void PrintNameVisitor::visit(Routine& node) 
{
    std::cout << "Visiting Routine\n";
    node.proto->accept(*this);
    node.body->accept(*this);
}
void PrintNameVisitor::visit(RoutineCall& node) 
{
    std::cout << "Visiting RoutineCall\n";
}
void PrintNameVisitor::visit(TypeDecl& node) 
{
    std::cout << "Visiting TypeDecl\n";
}
void PrintNameVisitor::visit(Unary& node) 
{
    std::cout << "Visiting Unary\n";
    node.operand->accept(*this);
}
void PrintNameVisitor::visit(Undefined& node) 
{
    std::cout << "Visiting Undefined\n";
}
void PrintNameVisitor::visit(Var& node) 
{
    std::cout << "Visiting Var\n";
    if (node.body != nullptr)
        node.body->accept(*this);
}
void PrintNameVisitor::visit(Variable& node) 
{
    std::cout << "Visiting Variable\n";
    node.var->accept(*this);
}
void PrintNameVisitor::visit(While& node) 
{
    std::cout << "Visiting While\n";
    node.expression->accept(*this);
    node.body->accept(*this);
}
void PrintNameVisitor::visit(Return& node) 
{
    std::cout << "Visiting Return\n";
    node.expression->accept(*this);
}
void PrintNameVisitor::visit(RecordRef& node) 
{
    std::cout << "Visiting RecordRef\n";
    node.record->accept(*this);
}
void PrintNameVisitor::visit(ArrayRef& node) 
{
    std::cout << "Visiting ArrayRef\n";
    node.array->accept(*this);
    node.pos->accept(*this);
}
void PrintNameVisitor::visit(Program& node) 
{
    std::cout << "Visiting Program\n";
}
void PrintNameVisitor::visit(Statements& node) 
{
    std::cout << "Visiting Statements\n";
}
void PrintNameVisitor::visit(Void& node) 
{
    std::cout << "Visiting Void\n";
}