#ifndef ILANG_WHILE_H
#define ILANG_WHILE_H

#include "node.h"

class While : public ASTNode {
    ASTNode *expression, *body;

public:
    While(ASTNode *expression, ASTNode *body);
};


#endif //ILANG_WHILE_H
