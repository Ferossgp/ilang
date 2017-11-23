#ifndef ILANG_INTEGER_H
#define ILANG_INTEGER_H

#include "expression.h"

class Integer : public Expression {

public:
    int value;
    Integer(const int value);
};

#endif //ILANG_INTEGER_H
