#include <string>

#include "variable.h"

using std::string;

VariableNode::VariableNode(const string &name)
        : name(name) {}

const string
VariableNode::getName() const {
    return name;
}