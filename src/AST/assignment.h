#ifndef ILANG_ASSIGNMENT_H
#define ILANG_ASSIGNMENT_H

#include "node.h"

class Assignment : public ASTNode {
    ASTNode *variable, *value;

public:
    Assignment(ASTNode *variable, ASTNode *value);
    void accept(Visitor &v) { v.visit(*this); };
};
#endif //ILANG_ASSIGNMENT_H
