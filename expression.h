#ifndef ILANG_Expression_H
#define ILANG_Expression_H

#include "node.h"
#include "type.h"

class Expression : public ASTNode {
public:
    Type *type;
    Expression();
};

#endif //ILANG_Expression_H
