#ifndef ILANG_UNDEFINED_H
#define ILANG_UNDEFINED_H

#include "type.h"

class Undefined : public Type {

public:
    Undefined() {
        type = types::Undefined;
    };
};

#endif //ILANG_UNDEFINED_H
