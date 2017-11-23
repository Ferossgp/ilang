#ifndef ILANG_TYPE_H
#define ILANG_TYPE_H

#include "node.h"
enum class types {
    Integer,
    Real,
    Boolean,
    Void,
    Undefined,
    Record,
    Array,
    Alias,
};

class Type : public ASTNode {
public:
    types type;
};

#endif //ILANG_TYPE_H
