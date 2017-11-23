#include "node.h"
#include "if.h"

If::If(ASTNode *condition, Statements *then, Statements *else_body)
        : condition(condition), then(then), else_body(else_body) {};

If::If(ASTNode *condition, Statements *then)
        : condition(condition), then(then) {};