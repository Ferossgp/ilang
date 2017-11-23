#include <string>
#include <vector>

#include "node.h"
#include "typedecl.h"

using std::string;

TypeDecl::TypeDecl(const string &identifier, Type *type):
        identifier(identifier), type(type) {};