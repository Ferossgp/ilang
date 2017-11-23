#ifndef ILANG_VAR_H
#define ILANG_VAR_H

#include <string>
#include <vector>

#include "node.h"
#include "type.h"

using std::string;
using std::vector;
using std::pair;

class Var : public ASTNode {
public:
    pair<string, Type*> var_decl;
    ASTNode *body;

    Var(const pair<string, Type*> &var_decl, ASTNode *body);
};

#endif //ILANG_VAR_H
