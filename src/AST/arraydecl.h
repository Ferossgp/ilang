#ifndef ILANG_ARRAY_H
#define ILANG_ARRAY_H
#include <vector>

#include "type.h"
#include "node.h"

class ArrayDecl : public ASTNode {
    ASTNode *expression;
    ASTNode *type;

public:
    ArrayDecl(ASTNode *expression, TypeNode *type);
};
#endif //ILANG_ARRAY_H
