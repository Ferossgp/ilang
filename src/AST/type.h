#ifndef ILANG_TYPE_H
#define ILANG_TYPE_H

#include <string>

#include "node.h"

using std::string;

class Type : public ASTNode {
    string name;
    ASTNode *type;

public:
    Type(const string &name, ASTNode *type);
};

#endif //ILANG_TYPE_H
