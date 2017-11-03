#ifndef ILANG_UNARY_H
#define ILANG_UNARY_H

#include "node.h"

class Unary: public ASTNode {
    char opcode;
    ASTNode *operand;

public:
    Unary(char opcode, ASTNode *operand);
};

#endif //ILANG_UNARY_H
