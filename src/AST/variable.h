#ifndef ILANG_VARIABLE_H
#define ILANG_VARIABLE_H
#include <string>

#include "node.h"

using std::string;

class Variable : public ASTNode {
    ASTNode *var, *value;

public:
    Variable(ASTNode *var, ASTNode *value);
};

#endif //ILANG_VARIABLE_H
