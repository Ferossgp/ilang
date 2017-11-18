#ifndef ILANG_BINARY_H
#define ILANG_BINARY_H

#include "expression.h"

class Binary : public Expression {
    char opchar;
    ASTNode *lhs, *rhs;

public:
    Binary(char opchar, ASTNode *lhs, ASTNode *rhs);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_BINARY_H
