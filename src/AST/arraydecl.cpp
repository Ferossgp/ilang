#include <vector>

#include "type.h"
#include "arraydecl.h"

using std::vector;

ArrayDecl::ArrayDecl(ASTNode *expression, TypeNode *type): expression(expression), type(type){}
