#ifndef ILANG_REAL_H
#define ILANG_REAL_H

#include "expression.h"

class Real : public Expression {
    double value;

public:
    Real();
    Real(double value);
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_REAL_H
