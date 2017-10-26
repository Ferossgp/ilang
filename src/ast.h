#ifndef ILANG_AST_H
#define ILANG_AST_H

#include <string>
#include <sstream>


class Expr {};

class Node {
    Node* leftBranch;
    Node* rightBranch;

public:
    Node() : leftBranch(NULL), rightBranch(NULL) {
    }

    Node(const Node& node) : leftBranch(NULL), rightBranch(NULL) {
        if (node.leftBranch) {
            leftBranch = node.leftBranch->clone();
        }
        if (node.rightBranch) {
            rightBranch = node.rightBranch->clone();
        }
    }

    void set(Node* left, Node* right=NULL) {
        if (leftBranch) {
            delete leftBranch;
        }
        leftBranch = left;

        if (rightBranch) {
            delete rightBranch;
        }
        rightBranch = right;
    }

    //virtual Node* clone() const = 0;

    const Node* get(bool left=true) const {
        if (left) {
            return leftBranch;
        }
        return rightBranch;
    }

    virtual ~Node() {
        if (leftBranch) {
            delete leftBranch;
        }
        if (rightBranch) {
            delete rightBranch;
        }
    }
};

class Operation : public Node {};
class BinaryOperation : public Node {};
class FunctionDecl : public Node {};
class FunctionCall : public Node {};
class FunctionBody : public Node {};
class Arguments : public Node {};
class Variable : public Node {};
class RecordDecl : public Node {};
class RecordName : public Node {};
class Array : public Node {};
class ArrayRef : public Node {};
class Quantifier : public Node {};
class While : public Node {};
class For : public Node {};

#endif //ILANG_AST_H