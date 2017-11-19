#include <string>

#include "variable.h"


Variable::Variable(ASTNode *var, ASTNode *value)
        : var(var), value(value) {}
