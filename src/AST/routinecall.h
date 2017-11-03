#ifndef ILANG_FUNCTIONCALL_H
#define ILANG_FUNCTIONCALL_H
#include <string>
#include <vector>

#include "node.h"

using std::string;
using std::vector;

class RoutineCall : public ASTNode {
    string callee;
    vector<ASTNode*> args;

public:
    RoutineCall(const string &callee, vector<ASTNode*> &args);
};

#endif //ILANG_FUNCTIONCALL_H
