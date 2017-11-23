#ifndef ILANG_FOR_H
#define ILANG_FOR_H
#include <string>

#include "node.h"
#include "statement.h"
using std::string;

class For: public ASTNode {
    string name;
    ASTNode *start, *end;
    Statements *body;

public:
    For(const string &name, ASTNode *start, ASTNode *end, Statements *body);
};


#endif //ILANG_FOR_H
