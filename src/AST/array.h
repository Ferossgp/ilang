#ifndef ILANG_ARRAY_H
#define ILANG_ARRAY_H
#include <vector>

#include "node.h"
#include "arrayref.h"

using std::vector;

class Array : public ASTNode {
    ASTNode *expression;
    ASTNode *type;
    vector<ASTNode> &refs;

public:
    Array(const vector<ArrayRef> &refs);
};
#endif //ILANG_ARRAY_H
