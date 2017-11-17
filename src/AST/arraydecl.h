#ifndef ILANG_ARRAY_H
#define ILANG_ARRAY_H
#include <vector>

#include "node.h"

class ArrayDecl : public ASTNode {
    ASTNode *expression;
    ASTNode *type;

public:
    ArrayDecl(ASTNode *expression, Type *type);
};
#endif //ILANG_ARRAY_H
