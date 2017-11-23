#ifndef ILANG_ERRORS_H
#define ILANG_ERRORS_H

#include "../AST/node.h"
#include "../AST/prototype.h"
#include "../AST/routine.h"


ASTNode *Error(const char *message);
Prototype *ErrorP(const char *message);
Routine *ErrorR(const char *message);

#endif //ILANG_ERRORS_H
