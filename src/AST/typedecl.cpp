#include <string>
#include <vector>

#include "node.h"
#include "typedecl.h"

using std::string;

TypeDecl::TypeDecl(const string &identifier, ASTNode *type):
        identifier(identifier), type(type) {};