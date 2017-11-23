#ifndef ILANG_UNARY_H
#define ILANG_UNARY_H

#include "expression.h"

class Unary: public Expression {
    char opcode;
    ASTNode *operand;

public:
    Unary(char opcode, ASTNode *operand);
};

#endif //ILANG_UNARY_H
