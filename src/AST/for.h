#ifndef ILANG_FOR_H
#define ILANG_FOR_H
#include <string>

#include "node.h"
#include "statements.h"
using std::string;

class For: public ASTNode {
public:
    string name;
    ASTNode *start, *end;

    Statements *body;
    For(const string &name, ASTNode *start, ASTNode *end, Statements *body);
    void accept(Visitor &v) { v.visit(*this); };
};


#endif //ILANG_FOR_H
