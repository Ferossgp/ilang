#ifndef ILANG_TYPEDECL_H
#define ILANG_TYPEDECL_H

#include <string>

#include "node.h"
#include "type.h"

class TypeDecl : public Type {

public:
    string identifier;
    Type *type;
    TypeDecl(const string &identifier, Type *type);
};

#endif //ILANG_TYPEDECL_H
