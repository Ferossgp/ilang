#ifndef ILANG_UNARY_H
#define ILANG_UNARY_H

#include "expression.h"

class Unary: public Expression {
public:
    char opcode;
	Expression *operand;

    Unary(char opcode, Expression *operand);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_UNARY_H
