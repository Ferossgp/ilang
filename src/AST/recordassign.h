#ifndef ILANG_RECORDASSIGN_H
#define ILANG_RECORDASSIGN_H

#include "node.h"

class RecordAssign : ASTNode {
    ASTNode *record, *ref, *value;

public:
    RecordAssign(ASTNode *record, ASTNode *ref, ASTNode *value);
};
#endif //ILANG_RECORDASSIGN_H
