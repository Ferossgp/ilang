#include "node.h"
#include "while.h"

While::While(ASTNode *expression, ASTNode *body)
        :  expression(expression),body(body) {}