#ifndef ILANG_VARIABLE_H
#define ILANG_VARIABLE_H

#include <string>

#include "expression.h"
#include "var.h"

using std::string;

class Variable : public Expression {
public:
    Var *var;

    Variable(Var *var);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_VARIABLE_H
