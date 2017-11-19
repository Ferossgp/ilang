#ifndef ILANG_ARRAYASSIGN_H
#define ILANG_ARRAYASSIGN_H

#include "node.h"

class ArrayAssign : ASTNode {
    ASTNode *array, *pos, *value;
public:
    ArrayAssign(ASTNode *array, ASTNode *pos, ASTNode *value);
};

#endif //ILANG_ARRAYASSIGN_H
