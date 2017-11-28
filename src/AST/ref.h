#ifndef ILANG_REF_H
#define ILANG_REF_H

#include <string>

#include "expression.h"
#include "var.h"

using std::string;

class Ref : public Expression {
public:
    Ref *next;
    Ref *prev;
    void add_next(Ref *node){
        next = node;
    }
    void add_prev(Ref *node){
        prev = node;   
    }
    void accept(Visitor &v) { v.visit(*this); };
};

#endif //ILANG_REF_H
