#include <string>
#include <vector>

#include "node.h"
#include "routinecall.h"

using std::string;
using std::vector;

RoutineCall::RoutineCall(const string &callee, vector<ASTNode*> &args):
        callee(callee), args(args) {}