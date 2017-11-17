#ifndef ILANG_VAR_H
#define ILANG_VAR_H

#include <string>
#include <vector>

#include "node.h"

using std::string;
using std::vector;
using std::pair;

class Var : public ASTNode {
    vector<pair<string, ASTNode*>> var_decl;
    ASTNode *body;

public:
    Var(const vector<pair<string, ASTNode* > &var_decl, STNode *body);
};

#endif //ILANG_VAR_H
