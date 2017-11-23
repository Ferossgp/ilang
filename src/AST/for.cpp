#include <string>

#include "node.h"
#include "for.h"

using std::string;

For::For(const string &name,
         ASTNode *start, ASTNode *end,
         Statements *body)
        : name(name), start(start), end(end), body(body) {}