#ifndef ILANG_VISITOR_H
#define ILANG_VISITOR_H
// #include "AST/prototype.h"

// class ASTNode;
class Prototype;
class Argument;
class Array;
class ArrayDecl;
class Assignment;
class Binary;
class Boolean;
class For;
class If;
class Integer;
class Real;
class RecordDecl;
class Routine;
class RoutineCall;
class TypeDecl;
class Unary;
class Var;
class Variable;
class While;

class Visitor
{
public:
    virtual void visit(Prototype& node) = 0;

    virtual void visit(Argument& node) = 0;
    virtual void visit(Array& node) = 0;
    virtual void visit(ArrayDecl& node) = 0;
    virtual void visit(Assignment& node) = 0;
    virtual void visit(Binary& node) = 0;
    virtual void visit(Boolean& node) = 0;
    //virtual void visit(Factor& node) = 0;
    virtual void visit(For& node) = 0;
    virtual void visit(If& node) = 0;
    virtual void visit(Integer& node) = 0;
    virtual void visit(Real& node) = 0;
    virtual void visit(RecordDecl& node) = 0;
    //virtual void visit(Relation& node) = 0;
    virtual void visit(Routine& node) = 0;
    virtual void visit(RoutineCall& node) = 0;
    //virtual void visit(Sign& node) = 0;
    //virtual void visit(Type& node) = 0;
    virtual void visit(TypeDecl& node) = 0;
    virtual void visit(Unary& node) = 0;
    virtual void visit(Var& node) = 0;
    virtual void visit(Variable& node) = 0;
    virtual void visit(While& node) = 0;
};

#endif 