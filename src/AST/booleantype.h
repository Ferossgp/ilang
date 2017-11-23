#ifndef ILANG_BOOLEANTYPE_H
#define ILANG_BOOLEANTYPE_H

#include "type.h"

class BooleanType : public Type {

public:
    BooleanType() {
         type = types::Boolean;
    };
};

#endif //ILANG_BOOLEANTYPE_H
