#ifndef ILANG_BINARY_H
#define ILANG_BINARY_H

#include "expression.h"
#include "../parsing/Lexer.h" //Move opchars globally

class Binary : public Expression {
public:
    opchars opchar;
    ASTNode *lhs, *rhs;

    Binary(opchars opchar, ASTNode *lhs, ASTNode *rhs);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_BINARY_H
