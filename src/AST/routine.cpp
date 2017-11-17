#include "node.h"
#include "prototype.h"
#include "routine.h"

Routine::Routine(Prototype *proto, ASTNode *body): proto(proto), body(body) {}