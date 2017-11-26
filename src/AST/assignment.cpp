#include "assignment.h"

Assignment::Assignment(ASTNode *variable, Expression *value, types lhs_type) : variable(variable), value(value), lhs_type{lhs_type} {}
