#ifndef ILANG_RETURN_H
#define ILANG_RETURN_H

#include "node.h"

class Return : ASTNode {
    ASTNode *expression;
public:
    Return::Return(ASTNode *expression);
};
#endif //ILANG_RETURN_H
