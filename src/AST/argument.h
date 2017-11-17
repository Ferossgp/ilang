#ifndef ILANG_ARGUMENTS_H
#define ILANG_ARGUMENTS_H

#include <string>
#include <vector>

#include "node.h"

using std::string;
using std::pair;

class Argument : public ASTNode {
    pair<string, ASTNode*> arg_decl;

public:
    Argument(const pair<string, ASTNode*> &arg_decl);
};


#endif //ILANG_ARGUMENTS_H
