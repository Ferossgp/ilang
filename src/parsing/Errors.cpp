#include <cstdio>

#include "Errors.h"

ASTNode *Error(const char *message) {
    fprintf(stderr, "Error, %s\n", message);
    return 0;
}
ASTNode *Error(const char *message, const char *name) {
    fprintf(stderr, "Error, %s in %s\n", message, name);
    return 0;
}
Prototype *ErrorP(const char *message) {
    Error(message);
    return 0;
}
Routine *ErrorR(const char *message) {
    Error(message);
    return 0;
}
Expression *ErrorE(const char *message) {
    Error(message);
    return 0;
}