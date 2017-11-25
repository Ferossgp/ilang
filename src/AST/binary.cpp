#include "node.h"
#include "binary.h"

Binary::Binary(opchars opchar, ASTNode *lhs, ASTNode *rhs):
        opchar(opchar), lhs(lhs), rhs(rhs) {}
        