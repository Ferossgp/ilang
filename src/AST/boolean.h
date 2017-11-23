#ifndef ILANG_BOOLEAN_H
#define ILANG_BOOLEAN_H

#include "expression.h"

class Boolean : public Expression {

public:
    bool value;
    Boolean(bool value);
};

#endif //ILANG_BOOLEAN_H
