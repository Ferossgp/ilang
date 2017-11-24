#ifndef ILANG_ARRAYASSIGN_H
#define ILANG_ARRAYASSIGN_H

#include "expression.h"

class ArrayRef : public Expression {
public:
    ASTNode *array, *pos;
    ArrayRef(ASTNode *array, ASTNode *pos): array{array}, pos{pos} {};
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_ARRAYASSIGN_H