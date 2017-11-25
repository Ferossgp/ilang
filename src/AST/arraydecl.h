#ifndef ILANG_ARRAY_H
#define ILANG_ARRAY_H

#include "node.h"
#include "type.h"
#include "expression.h"

class ArrayDecl : public Type {

public:
    Expression *expression;
    Type *array_type;
    ArrayDecl(Expression *expression, Type *array_type);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_ARRAY_H
