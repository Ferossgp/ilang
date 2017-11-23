
#include <string>
#include <vector>

#include "node.h"
#include "argument.h"

using std::string;
using std::pair;


Argument::Argument(const pair<string, Type*> &arg_decl):
        arg_decl(arg_decl) {}