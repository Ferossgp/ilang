#include "node.h"
#include "if.h"

IfNode::IfNode(ASTNode *condition, ASTNode *then, ASTNode *else_body)
        : condition(condition), then(then), else_body(else_body) {};

IfNode::IfNode(ASTNode *condition, ASTNode *then)
        : condition(condition), then(then) {};