#ifndef ILANG_VISITOR_H
#define ILANG_VISITOR_H
// #include "AST/prototype.h"

// class ASTNode;
class Prototype;

class Visitor
{
public:
    virtual void visit(Prototype& node) = 0;
};

#endif 
