#ifndef ILANG_ROUTINECALL_H
#define ILANG_ROUTINECALL_H

#include <vector>

#include "expression.h"
#include "routine.h"

using std::vector;

class RoutineCall : public Expression {
public:
    Routine *callee;
    vector<ASTNode*> args;

    RoutineCall(Routine *callee, vector<ASTNode*> &args);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_ROUTINECALL_H
