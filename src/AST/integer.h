#ifndef ILANG_INTEGER_H
#define ILANG_INTEGER_H

#include "node.h"

class Integer : public ASTNode {
    int value;

public:
    Integer();
    Integer(int value);
};

#endif //ILANG_INTEGER_H
