#ifndef ILANG_ARGUMENTS_H
#define ILANG_ARGUMENTS_H

#include <string>
#include <vector>

#include "node.h"
#include "type.h"

using std::string;
using std::pair;

class Argument : public ASTNode {
    pair<string, Type*> arg_decl;

public:
    Argument(const pair<string, Type*> &arg_decl);
        void accept(Visitor &v) { v.visit(*this); };

};


#endif //ILANG_ARGUMENTS_H
