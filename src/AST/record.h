#ifndef ILANG_RECORD_H
#define ILANG_RECORD_H

#include <vector>

#include "node.h"

using std::vector;
using std::pair;
using std::string;

class Record : public ASTNode {
    vector<ASTNode*> &refs;

public:
    Array(const vector<ASTNode*> &refs);
};

#endif //ILANG_RECORD_H
