#ifndef ILANG_ARRAY_H
#define ILANG_ARRAY_H

#include "node.h"
#include "type.h"

class ArrayDecl : public ASTNode {
    ASTNode *expression;
    ASTNode *type;

public:
    ArrayDecl(ASTNode *expression, ASTNode *type);
};

#endif //ILANG_ARRAY_H
