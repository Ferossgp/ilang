#include <string>
#include <vector>

#include "prototype.h"

using std::string;
using std::vector;

Prototype::Prototype(const string &name,
                     const vector<ASTNode*> &args)
        : name(name), args(args) {}