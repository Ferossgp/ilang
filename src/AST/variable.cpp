#include <string>

#include "variable.h"

using std::string;

Variable::Variable(const string &name)
        : name(name) {}

const string
Variable::getName() const {
    return name;
}