#ifndef ILANG_INTEGERTYPE_H
#define ILANG_INTEGERTYPE_H

#include "type.h"

class IntegerType : public Type {

public:
    IntegerType() {
        type = types::Integer;
    };
};

#endif //ILANG_INTEGERTYPE_H
