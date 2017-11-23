#ifndef ILANG_FUNCTION_H
#define ILANG_FUNCTION_H
#include <string>

#include "node.h"
#include "prototype.h"
#include "statements.h"

using std::string;

class Routine : public ASTNode {
    Prototype *proto;
    Statements *body;

public:
    Routine(Prototype *proto, Statements *body);
};

#endif //ILANG_FUNCTION_H
