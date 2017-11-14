
#include <string>
#include <vector>

#include "node.h"
#include "var.h"

using std::string;
using std::pair;


Var::Var(const pair<string, ASTNode*> &var_decl,ASTNode *body):
        var_decl(var_decl), body(body) {}