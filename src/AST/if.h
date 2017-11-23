#ifndef ILANG_IF_H
#define ILANG_IF_H

#include "node.h"
#include "statements.h"

class If : public ASTNode {
    ASTNode *condition;
    Statements *then, *else_body;

public:
    If(ASTNode *condition, Statements *then, Statements *else_body);
    If(ASTNode *condition, Statements *then);
};


#endif //ILANG_IF_H
