#ifndef ILANG_FUNCTION_H
#define ILANG_FUNCTION_H
#include <string>

#include "node.h"
#include "prototype.h"

using std::string;

class Routine : public ASTNode {
    Prototype *proto;
    ASTNode *body;

public:
    Routine(Prototype *proto, ASTNode *body);
};

#endif //ILANG_FUNCTION_H
