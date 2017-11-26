#ifndef ILANG_BINARY_H
#define ILANG_BINARY_H

#include "expression.h"
#include "../parsing/Lexer.h" //Move opchars globally

class BinaryOpcode {
public:
    opchars op;
    bool isMath;
    bool isLogic;
    bool isCmp;
    bool isEq;

    BinaryOpcode(opchars op) : op(op) {
        isMath = op == opchars::DIV || op == opchars::MINUS || op == opchars::MOD || op == opchars::MUL || op == opchars::PLUS;
        isLogic = op == opchars::AND || op == opchars::OR || op == opchars::XOR;
        isCmp = op == opchars::HIGH || op == opchars::HIGHEQ || op == opchars::LESS || op == opchars::LESSEQ;
        isEq = op == opchars::EQUAL || op == opchars::NOTEQ;
    }
};

class Binary : public Expression {
public:
    opchars opchar;
    Expression *lhs, *rhs;

    Binary(opchars opchar, ASTNode *lhs, ASTNode *rhs);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_BINARY_H
