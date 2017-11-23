#include "../visitor.h"

#include "../AST/prototype.h"
#include "../AST/argument.h"

#include "../AST/array.h"
#include "../AST/arraydecl.h"
#include "../AST/assignment.h"
#include "../AST/binary.h"
#include "../AST/boolean.h"
#include "../AST/for.h"
#include "../AST/if.h"
#include "../AST/integer.h"
#include "../AST/real.h"
#include "../AST/recorddecl.h"
#include "../AST/routine.h"
#include "../AST/routinecall.h"
#include "../AST/typedecl.h"
#include "../AST/unary.h"
#include "../AST/var.h"
#include "../AST/variable.h"
#include "../AST/while.h"

class TypeDeduceVisitor : public Visitor
{
public:
    void visit(Prototype& node);

    void visit(Argument& node);
    void visit(Array& node);
    void visit(ArrayDecl& node);
    void visit(Assignment& node);
    void visit(Binary& node);
    void visit(Boolean& node);
    //void visit(Factor& node);
    void visit(For& node);
    void visit(If& node);
    void visit(Integer& node);
    void visit(Real& node);
    //void visit(Record& node);
    void visit(RecordDecl& node);
    //void visit(Relation& node);
    void visit(Routine& node);
    void visit(RoutineCall& node);
    //void visit(Sign& node);
    //void visit(Type& node);
    void visit(TypeDecl& node);
    void visit(Unary& node);
    void visit(Var& node);
    void visit(Variable& node);
    void visit(While& node);
};