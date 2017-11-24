#include <vector>

#include "node.h"
#include "routinecall.h"

using std::vector;

RoutineCall::RoutineCall(Routine *callee, vector<ASTNode*> &args):
        callee(callee), args(args) {}