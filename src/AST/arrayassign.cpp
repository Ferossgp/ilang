#include "node.h"
#include "arrayassign.h"

ArrayAssign::ArrayAssign(ASTNode *array, ASTNode *pos, ASTNode *value):
    array(array), pos(pos), value(value) {};