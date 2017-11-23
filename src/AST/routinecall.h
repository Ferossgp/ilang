#ifndef ILANG_ROUTINECALL_H
#define ILANG_ROUTINECALL_H
#include <string>
#include <vector>

#include "expression.h"

using std::string;
using std::vector;

class RoutineCall : public Expression {
public:
    string callee;
    vector<ASTNode*> args;

    RoutineCall(const string &callee, vector<ASTNode*> &args);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_ROUTINECALL_H
