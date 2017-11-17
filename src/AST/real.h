#ifndef ILANG_REAL_H
#define ILANG_REAL_H

#include "node.h"

class Real : public ASTNode {
    double value;

public:
    Real();
    Real(double value);
};

#endif //ILANG_REAL_H
