#ifndef ILANG_ROUTINECALL_H
#define ILANG_ROUTINECALL_H

#include <vector>

#include "expression.h"

using std::vector;

class RoutineCall : public Expression {
public:
    ASTNode *callee;
    vector<ASTNode*> args;

    RoutineCall(ASTNode *callee, vector<ASTNode*> &args);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_ROUTINECALL_H
