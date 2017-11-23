#ifndef ILANG_ARGUMENTS_H
#define ILANG_ARGUMENTS_H

#include <string>
#include <vector>

#include "node.h"
#include "type"

using std::string;
using std::pair;

class Argument : public ASTNode {
    pair<string, Type*> arg_decl;

public:
    Argument(const pair<string, Type*> &arg_decl);
};


#endif //ILANG_ARGUMENTS_H
