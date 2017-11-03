#include <vector>

#include "node.h"
#include "arraydecl.h"

using std::vector;

ArrayDecl::ArrayDecl(ASTNode *expression, Type *type): expression(expression), type(type){}