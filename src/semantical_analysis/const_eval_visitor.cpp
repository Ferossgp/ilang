#include "const_eval_visitor.h"
#include "error.h"

void ConstEvalVisitor::visit(Prototype& node) {
}
void ConstEvalVisitor::visit(ArrayDecl& node) {
    unwrap(node.expression);
}
void ConstEvalVisitor::visit(ArrayRef& node) {
    node.array->accept(*this);
    unwrap(node.pos);
}
void ConstEvalVisitor::visit(Assignment& node) {
    node.variable->accept(*this);
    unwrap(node.value);
}
void ConstEvalVisitor::visit(Binary& node) {
    unwrap(node.lhs);
    unwrap(node.rhs);
    node.isConst = node.lhs->isConst && node.rhs->isConst;
}
void ConstEvalVisitor::visit(Boolean& node) {
}
void ConstEvalVisitor::visit(BooleanType& node) {
    reportError("bug: ConstEvalVisitor: visit BooleanType node");
}
void ConstEvalVisitor::visit(Cast& node) {
    unwrap(node.value);
    node.isConst = node.value->isConst;
}
void ConstEvalVisitor::visit(For& node) {
    node.start->accept(*this);
    node.end->accept(*this);
    node.body->accept(*this);
}
void ConstEvalVisitor::visit(If& node) {
    node.condition->accept(*this);
    node.then->accept(*this);
    if (node.else_body) {
        node.else_body->accept(*this);
    }
}
void ConstEvalVisitor::visit(Integer& node) {
}
void ConstEvalVisitor::visit(IntegerType& node) {
    reportError("bug: ConstEvalVisitor: visit IntegerType node");
}
void ConstEvalVisitor::visit(Real& node) {
}
void ConstEvalVisitor::visit(RealType& node) {
    reportError("bug: ConstEvalVisitor: visit RealType node");
}
void ConstEvalVisitor::visit(RecordDecl& node) {
    for (auto x : node.refs) {
        x->accept(*this);
    }
}
void ConstEvalVisitor::visit(Routine& node) {
    node.body->accept(*this);
}
void ConstEvalVisitor::visit(RoutineCall& node) {
    for (auto x : node.args) {
        x->accept(*this);
    }
}
void ConstEvalVisitor::visit(TypeDecl& node) {
}
// TODO: wait: "not" unary operator decoding
// TODO: "not" unary operator logic
void ConstEvalVisitor::visit(Unary& node) {
    unwrap(node.operand);
    node.isConst = node.operand->isConst;
}
void ConstEvalVisitor::visit(Undefined& node) {
    reportError("bug: ConstEvalVisitor: visit Undefined node");
}
void ConstEvalVisitor::visit(Var& node) {
    node.body->accept(*this);
}
void ConstEvalVisitor::visit(Variable& node) {
}
void ConstEvalVisitor::visit(While& node) {
    node.expression->accept(*this);
    node.body->accept(*this);
}
void ConstEvalVisitor::unwrap(Expression *&value) {
    value->accept(*this);
    if (value->isConst) {
        value = value->eval();
    }
}
