#ifndef ILANG_RECORDREF_H
#define ILANG_RECORDREF_H

#include <string>
#include "expression.h"

class RecordRef : Expression {

public:
    ASTNode *record;
    std::string ref;
    RecordRef (ASTNode *record, std::string ref) {};
};

#endif //ILANG_RECORDREF_H
