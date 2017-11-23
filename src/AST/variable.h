#ifndef ILANG_VARIABLE_H
#define ILANG_VARIABLE_H
#include <string>

#include "expression.h"

using std::string;

class Variable : public Expression {
public:
    ASTNode *var;

    Variable(ASTNode *var);
};

#endif //ILANG_VARIABLE_H
