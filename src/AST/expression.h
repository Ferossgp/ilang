#ifndef ILANG_EXPRESSION_H
#define ILANG_EXPRESSION_H


#include "node.h"
#include "type.h"

class Expression : public ASTNode {
public:
    Type *type;
    Expression() : type(types::Undefined) {}
};

#endif //ILANG_EXPRESSION_H
