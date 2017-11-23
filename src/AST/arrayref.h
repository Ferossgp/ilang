#ifndef ILANG_ARRAYASSIGN_H
#define ILANG_ARRAYASSIGN_H

#include "expression.h"

class ArrayAssign : Expression {
public:
    ASTNode *array, *pos;
    ArrayAssign(ASTNode *array, ASTNode *pos);
};

#endif //ILANG_ARRAYASSIGN_H
