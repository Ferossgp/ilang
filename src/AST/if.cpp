#include "node.h"
#include "if.h"

If::If(ASTNode *condition, ASTNode *then, ASTNode *else_body)
        : condition(condition), then(then), else_body(else_body) {};

If::If(ASTNode *condition, ASTNode *then)
        : condition(condition), then(then) {};