#ifndef ILANG_PROTOTYPE_H
#define ILANG_PROTOTYPE_H
#include <string>
#include <vector>

#include "node.h"

using std::string;
using std::vector;

class Prototype : public ASTNode {
    string name;
    vector<ASTNode*> args;

public:
    Prototype(const string &name, const vector<ASTNode*> &args);
    const string &getName() const { return name; }
    const vector<ASTNode*>& getArgs() { return args; };
    void accept(Visitor &v) { v.visit(*this); };
};
#endif //ILANG_PROTOTYPE_H
