#ifndef ILANG_UNARY_H
#define ILANG_UNARY_H

#include "expression.h"

class Unary: public Expression {
public:
    char opcode;
    ASTNode *operand;

    Unary(char opcode, ASTNode *operand);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_UNARY_H
