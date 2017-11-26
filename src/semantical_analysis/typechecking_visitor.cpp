#include "typechecking_visitor.h"
#include <iostream>

/*
    In routine's prototype we can do nothing
*/
void TypeCheckingVisitor::visit(Prototype& node)
{
    return;
}

/*
    Check that array's size is an integer constant
*/
void TypeCheckingVisitor::visit(ArrayDecl& node)
{
    auto sizeExpression = (Expression*) node.expression;
    if (sizeExpression->type->type != types::Integer)
    {
        reportError("Size of array is not compile-time integer constanst\n");
    }
}

/*
    Check that both sides of the assignment are of the same or
    compatible types. If second variant, cast it
*/
void TypeCheckingVisitor::visit(Assignment& node)
{
    // Variable, array or record reference
    auto left = (Expression*) node.variable;
    std::cout << "Left side of ass\n";
    auto left_type = left->type->type;
    std::cout << "Left side type of ass\n";
    auto right = (Expression*) node.value;
    std::cout << "Right side of ass\n";
    auto right_type = right->type->type;

    left->accept(*this);
    right->accept(*this);

    if (left_type == types::Integer && right_type == types::Integer)
    {
        return;
    }
    else if (left_type == types::Integer && right_type == types::Real)
    {
        auto cast_node = new Cast { right, new IntegerType() };
        node.value = cast_node;
    }
    else if (left_type == types::Integer && right_type == types::Boolean)
    {
        auto cast_node = new Cast { right, new BooleanType() };
        node.value = cast_node;
    }
    else if (left_type == types::Real && right_type == types::Integer)
    {
        auto cast_node = new Cast { right, new IntegerType() };
        node.value = cast_node;
    }
    else if (left_type == types::Real && right_type == types::Real)
    {
        return;
    }
    else if (left_type == types::Real && right_type == types::Boolean)
    {
        auto cast_node = new Cast { right, new RealType() };
        node.value = cast_node;
    }
    else if (left_type == types::Boolean && right_type == types::Integer)
    {
        auto cast_node = new Cast { right, new BooleanType() };
        node.value = cast_node;
    }
    else if (left_type == types::Boolean && right_type == types::Boolean)
    {
        return;
    }
    else if (left_type == types::Array && right_type == types::Array)
    {
        if (*left->type != *right->type)
        {
            reportError("Trying to assign arrays of different types\n");
        }
        return;
    }
    else if (left_type == types::Record && right_type == types::Record)
    {
        if (*left->type != *right->type)
        {
            reportError("Trying to assign records of different types\n");
        }
        return;
    }
    // else
    // {
    //     reportError("Trying to assign incompatible types\n");
    // }
}

/*
    Everything was checked during the previous pass
*/
void TypeCheckingVisitor::visit(Binary& node)
{
    return;
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(Boolean& node)
{
    return;
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(BooleanType& node)
{
    return;
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(Cast& node)
{
    return;
}

/*
    Check that expression in FOR is of integer type
    Go through statements in FOR
*/
void TypeCheckingVisitor::visit(For& node)
{
    auto from = (Expression*) node.start;
    auto until = (Expression*) node.end;
    if (from->type->type != types::Integer || until->type->type != types::Integer)
        reportError("Variable in FOR loop is not of integer type!\n");

    node.body->accept(*this);
}

/*
    Check that expression in IF is of boolean type
    Go through all statements in both branches
*/
void TypeCheckingVisitor::visit(If& node)
{
    std::cout << "FOO\n";
    auto expr = (Expression*) node.condition;
    std::cout << (int) expr->type->type << "\n";
    if (expr->type->type != types::Boolean)
        reportError("Type of expression in if is not boolean!\n");

    node.then->accept(*this);
    if (!node.else_body)
        node.else_body->accept(*this);
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(Integer& node)
{
    return;
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(IntegerType& node)
{
    return;
}

void TypeCheckingVisitor::visit(Real& node)
{
    return;
}
/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(RealType& node)
{
    return;
}

/*
    Go through all declarations in the record
*/
void TypeCheckingVisitor::visit(RecordDecl& node)
{
    for (int i = 0; i < node.refs.size(); i++)
        node.refs[i]->accept(*this);
}

/*
    Go through all routine's statements
*/
void TypeCheckingVisitor::visit(Routine& node)
{
    // Go through all statements in body
    lastVisitedRoutine = &node;
    node.body->accept(*this);
}

/*
    Check that arguments are exactly as in the routine declaration
*/
void TypeCheckingVisitor::visit(RoutineCall& node)
{
    auto actualArguments = node.args;
    auto expectedArguments = node.callee->proto->args;
    auto routineName = node.callee->proto->name;

    // Check arguments
    auto argsLength = expectedArguments.size();
    if (actualArguments.size() != argsLength)
        reportError("Arguments of function " + routineName + " are incorrect! Expected " +
            std::to_string(argsLength) + ", got " + std::to_string(actualArguments.size()) + "\n");

    for (int i = 0; i < argsLength; i++)
    {
        if (((Expression*) expectedArguments[i])->type->type != ((Expression*) actualArguments[i])->type->type)
            reportError("Arguments of function " + routineName +
                " are incorrect! Expected another type on " + std::to_string(i) + "\n");
    }
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(TypeDecl& node)
{
    return;
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(Unary& node)
{
    return;
}

/*
    We cannot reach the undefined in normal case
*/
void TypeCheckingVisitor::visit(Undefined& node)
{
    reportError("Undefined reached during the type checking!\n");
}

/*
    Check that initial value is of declared type, if exists
*/
void TypeCheckingVisitor::visit(Var& node)
{
    auto declaredType = node.var_decl.second;
    if (node.body) {
        auto actualType = ((Expression*)node.body)->type;
        if (*declaredType != *actualType) {
            reportError("Initial value of variable " + node.var_decl.first + " is not of the declared type!\n");
        }
    }
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(Variable& node)
{
    return;
}

/*
    Check expression in WHILE for boolean
    Go through statements in loop
*/
void TypeCheckingVisitor::visit(While& node)
{
    auto expr = (Expression*) node.expression;
    if (expr->type->type != types::Boolean)
        reportError("Expression in WHILE is not of boolean type!\n");

    node.body->accept(*this);
}

/*
    Check that routine's return value is the same as declared
*/
void TypeCheckingVisitor::visit(Return& node)
{
    if (*((Expression*)node.expression)->type != *lastVisitedRoutine->proto->type)
        reportError("Routine " + lastVisitedRoutine->proto->name + " has incorrect " +
        "return value!\n");
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(RecordRef& node)
{
    return;
}

/*
    Check that called position is integer
*/
void TypeCheckingVisitor::visit(ArrayRef& node)
{
    auto position = (Expression*) node.pos;
    if (position->type->type != types::Integer)
        reportError("Trying to call array with not-integer type!\n");
}

/*
    Entry point
*/
void TypeCheckingVisitor::visit(Program& node)
{
    for (auto statement: node.program)
    {
        statement->accept(*this);
    }
}

/*
    Visit every statement
*/
void TypeCheckingVisitor::visit(Statements& node)
{
    for (auto statement : node.statements)
        statement->accept(*this);
}

/*
    Can do nothing
*/
void TypeCheckingVisitor::visit(Void& node)
{
    return;
}
