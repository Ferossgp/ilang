#ifndef ILANG_EXPRESSION_H
#define ILANG_EXPRESSION_H


#include "node.h"
#include "type.h"
#include "undefined.h"

class Expression : public ASTNode {
public:
    Type *type;
    Expression() : type(new Undefined()) {}
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_EXPRESSION_H
