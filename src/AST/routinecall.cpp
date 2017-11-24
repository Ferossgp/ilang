#include <vector>

#include "node.h"
#include "routinecall.h"

using std::vector;

RoutineCall::RoutineCall(ASTNode *callee, vector<ASTNode*> &args):
        callee(callee), args(args) {}