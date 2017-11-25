#include "typededuce_visitor.h"
#include "error.h"

void TypeDeduceVisitor::visit(Prototype& node) {
    reportError("bug: TypeDeduceVisitor: visit Prototype node");
}
void TypeDeduceVisitor::visit(ArrayDecl& node) {
    node.expression->accept(*this);
}
void TypeDeduceVisitor::visit(Assignment& node) {
    node.value->accept(*this);
}
// TODO: wait: "and", "or", "xor", "/=", "<=", ">=" binary operator decoding
// TODO: if non-equal then cast
// TODO: implement
void TypeDeduceVisitor::visit(Binary& node) {
    node.lhs->accept(*this);
    node.rhs->accept(*this);
    if (!Type::isPrimitive(*node.lhs->type) || !Type::isPrimitive(*node.rhs->type)) {
        reportError("error: TypeDeduceVisitor: binary with non-primitive");
    }
    // cmp, int|real->bool
    // log, bool->bool
    // math, int|real->int|real
    if (strchr("+-/*", node.opchar)) {
        if (node.lhs->type != node.rhs->type) {
            // ...
        }
        // ...
    }
    reportError("bug: TypeDeduceVisitor: visit Binary node not implemented");
}
void TypeDeduceVisitor::visit(Boolean& node) {
    reportError("bug: TypeDeduceVisitor: visit Boolean node");
}
void TypeDeduceVisitor::visit(BooleanType& node) {
    reportError("bug: TypeDeduceVisitor: visit BooleanType node");
}
void TypeDeduceVisitor::visit(Cast& node) {
    reportError("bug: TypeDeduceVisitor: visit cast node");
}
void TypeDeduceVisitor::visit(For& node) {
    node.start->accept(*this);
    node.end->accept(*this);
    node.body->accept(*this);
}
void TypeDeduceVisitor::visit(If& node) {
    node.condition->accept(*this);
    node.then->accept(*this);
    if (node.else_body) {
        node.else_body->accept(*this);
    }
}
void TypeDeduceVisitor::visit(Integer& node) {
    reportError("bug: TypeDeduceVisitor: visit Integer node");
}
void TypeDeduceVisitor::visit(IntegerType& node) {
    reportError("bug: TypeDeduceVisitor: visit IntegerType node");
}
void TypeDeduceVisitor::visit(Real& node) {
    reportError("bug: TypeDeduceVisitor: visit Real node");
}
void TypeDeduceVisitor::visit(RealType& node) {
    reportError("bug: TypeDeduceVisitor: visit RealType node");
}
void TypeDeduceVisitor::visit(RecordDecl& node) {
}
void TypeDeduceVisitor::visit(Routine& node) {
    node.body->accept(*this);
}
void TypeDeduceVisitor::visit(RoutineCall& node) {
    for (auto x : node.args) {
        x->accept(*this);
    }
    node.type = node.callee->proto->type;
}
void TypeDeduceVisitor::visit(TypeDecl& node) {
}
// TODO: wait: "not" unary operator decoding
// TODO: "not" unary operator logic
void TypeDeduceVisitor::visit(Unary& node) {
    node.operand->accept(*this);
    if (strchr("+-", node.opcode)) {
        if (*node.operand->type == types::Boolean) {
            node.operand = new Cast(node.operand, new IntegerType());
        }
        node.type = node.operand->type;
        return;
    }
    reportError("bug: TypeDeduceVisitor: unexpected unary opcode");
}
void TypeDeduceVisitor::visit(Undefined& node) {
    reportError("bug: TypeDeduceVisitor: visit Undefined node");
}
void TypeDeduceVisitor::visit(Var& node) {
    node.body->accept(*this);
    if (*node.var_decl.second == types::Undefined) {
        node.var_decl.second = node.body->type;
    }
}
void TypeDeduceVisitor::visit(Variable& node) {
    node.type = node.var->var_decl.second;
}
void TypeDeduceVisitor::visit(While& node) {
    node.expression->accept(*this);
    node.body->accept(*this);
}