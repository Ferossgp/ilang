#ifndef ILANG_TYPEDECL_H
#define ILANG_TYPEDECL_H

#include <string>

#include "node.h"

using std::string;

class TypeDecl : public ASTNode {
    string identifier;
    ASTNode *type;

public:
    TypeDecl(const string &identifier, ASTNode *type);
};

#endif //ILANG_TYPEDECL_H
