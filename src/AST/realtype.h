#ifndef ILANG_REALTYPE_H
#define ILANG_REALTYPE_H

#include "type.h"

class RealType : public Type {

public:
    RealType() {
        type = types::Real;
    };
};

#endif //ILANG_REALTYPE_H
