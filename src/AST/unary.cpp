#include "node.h"
#include "unary.h"

Unary::Unary(char opcode, ASTNode *operand)
        : opcode(opcode), operand(operand) {}

