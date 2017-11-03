#ifndef ILANG_ARRAYREF_H
#define ILANG_ARRAYREF_H

#include "node.h"

class ArrayRef : public ASTNode {
    ASTNode name;

public:
    ArrayRef(const ASTNode &name);
};

#endif //ILANG_ARRAYREF_H
