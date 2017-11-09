#include <string>
#include <vector>

#include "prototype.h"

using std::string;
using std::vector;

Prototype::Prototype(const string &name,
                     const vector<string> &args)
        : name(name), args(args) {}