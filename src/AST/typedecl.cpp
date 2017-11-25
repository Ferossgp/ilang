#include <string>
#include <vector>

#include "node.h"
#include "typedecl.h"

using std::string;

TypeDecl::TypeDecl(const string &identifier, Type *original):
        identifier(identifier), original(original) {
    type = types::Alias;
}
