#ifndef ILANG_RETURN_H
#define ILANG_RETURN_H

#include "node.h"

class Return : ASTNode {
public:
    ASTNode *expression;
    Return::Return(ASTNode *expression);
    void accept(Visitor &v) { v.visit(*this); };
};
#endif //ILANG_RETURN_H
