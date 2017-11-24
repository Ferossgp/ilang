#ifndef ILANG_IF_H
#define ILANG_IF_H

#include "node.h"
#include "statements.h"

class If : public ASTNode {
public:
    ASTNode *condition;
    Statements *then, *else_body;

    If(ASTNode *condition, Statements *then, Statements *else_body);
    If(ASTNode *condition, Statements *then);
    void accept(Visitor &v) { v.visit(*this); };
};


#endif //ILANG_IF_H
