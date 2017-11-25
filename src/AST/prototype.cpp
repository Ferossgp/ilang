#include <string>
#include <vector>

#include "prototype.h"

using std::string;
using std::vector;

Prototype::Prototype(const string &name,
                     const vector<Argument*> &args,
                     Type *type)
        : name(name), args(args), type(type) {}
