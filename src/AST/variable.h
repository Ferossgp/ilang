#ifndef ILANG_VARIABLE_H
#define ILANG_VARIABLE_H
#include <string>

#include "node.h"

using std::string;

class Variable : public ASTNode {
    string name;

public:
    Variable(const string &name);
};

#endif //ILANG_VARIABLE_H
