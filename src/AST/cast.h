#ifndef ILANG_CAST_H
#define ILANG_CAST_H

#include "expression.h"

class Cast : public Expression {

public:
    Expression* value;

    Cast(Expression* expression, Type* type);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_CAST_H
