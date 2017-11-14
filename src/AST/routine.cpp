#include "node.h"
#include "prototype.h"
#include "routine.h"

Routine::Routine(PrototypeNode *proto, ASTNode *body): proto(proto), body(body) {}