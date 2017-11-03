#ifndef ILANG_IF_H
#define ILANG_IF_H

#include "node.h"

class If : public ASTNode {
    ASTNode *condition, *then, *else_conditon;

public:
    If(ASTNode *cond, ASTNode *then, ASTNode *else_condition);
};


#endif //ILANG_IF_H
