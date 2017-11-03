#include "node.h"
#include "binary.h"

Binary::Binary(char opchar, ASTNode *lhs, ASTNode *rhs):
        opchar(opchar), lhs(lhs), rhs(rhs) {}