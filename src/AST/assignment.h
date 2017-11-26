#ifndef ILANG_ASSIGNMENT_H
#define ILANG_ASSIGNMENT_H

#include "node.h"
#include "expression.h"

class Assignment : public ASTNode {
public:

    ASTNode *variable;
    Expression *value;
    types lhs_type;

    Assignment(ASTNode *variable, Expression *value, types lhs_type);
    void accept(Visitor &v) { v.visit(*this); };
};
#endif //ILANG_ASSIGNMENT_H
