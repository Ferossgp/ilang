#include "../visitor.h"
#include "../AST/prototype.h"

class CodegenVisitor : Visitor
{
public:
    void visit(Prototype& p);
};
