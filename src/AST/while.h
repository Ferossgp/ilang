#ifndef ILANG_WHILE_H
#define ILANG_WHILE_H

#include "node.h"
#include "statements.h"

class While : public ASTNode {
    ASTNode *expression;
    Statements *body;

public:
    While(ASTNode *expression, Statements *body);
};


#endif //ILANG_WHILE_H
