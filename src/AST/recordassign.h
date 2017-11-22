#ifndef ILANG_RECORDASSIGN_H
#define ILANG_RECORDASSIGN_H

#include "node.h"

class RecordAssign : ASTNode {
    ASTNode *record, *value;
    std::string ref;

public:
    RecordAssign(ASTNode *record, std::string ref, ASTNode *value);
};
#endif //ILANG_RECORDASSIGN_H
