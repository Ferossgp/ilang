#ifndef ILANG_BINARY_H
#define ILANG_BINARY_H

#include "expression.h"
#include "../parsing/Lexer.h" //Move opchars globally

class Binary : public Expression {
    opchars opchar;
    ASTNode *lhs, *rhs;

public:
    Binary(opchars opchar, ASTNode *lhs, ASTNode *rhs);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_BINARY_H
