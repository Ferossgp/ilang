#ifndef ILANG_ASSIGNMENT_H
#define ILANG_ASSIGNMENT_H

#import "node.h"

class Assignment : ASTNode {
    std::string element;
    ASTNode *value;
};
#endif //ILANG_ASSIGNMENT_H
