#include <string>

#include "variable.h"

Variable::Variable(Var *var)
        : var(var) 
        {
                type = ((Var*) var)->var_decl.second;
        }
