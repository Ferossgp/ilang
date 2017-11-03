#ifndef ILANG_FOR_H
#define ILANG_FOR_H
#include <string>

#include "node.h"
using std::string;

class For: public ASTNode {
    string name;
    ASTNode *start, *end, *step, *body;

public:
    For(const string &name, ASTNode *start, ASTNode *end, ASTNode *step, ASTNode *body);
};


#endif //ILANG_FOR_H
