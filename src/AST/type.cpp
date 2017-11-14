#include <string>

#include "node.h"
#include "type.h"

using std::string;

Type::Type(const string &name,ASTNode *type):
        name(name), type(type) {}