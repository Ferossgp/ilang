#include <string>

#include "node.h"
#include "for.h"

using std::string;

For::For(const string &name,
         ASTNode *start, ASTNode *end,
         ASTNode *step,
         ASTNode *body)
        : name(var_name), start(start), end(end), step(step), body(body) {}