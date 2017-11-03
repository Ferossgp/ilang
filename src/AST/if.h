#ifndef ILANG_IF_H
#define ILANG_IF_H

#include "node.h"

class If : public ASTNode {
    ASTNode *condition, *then, *else_body;

public:
    If(ASTNode *condition, ASTNode *then, ASTNode *else_body);
};


#endif //ILANG_IF_H
