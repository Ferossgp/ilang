#ifndef ILANG_ASSIGNMENT_H
#define ILANG_ASSIGNMENT_H

#include "node.h"

class Assignment : ASTNode {
    ASTNode *variable, *value;

public:
    Assignment(ASTNode *variable, ASTNode *type);
};
#endif //ILANG_ASSIGNMENT_H
