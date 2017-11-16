#ifndef ILANG_BOOLEAN_H
#define ILANG_BOOLEAN_H

class Boolean : public ASTNode {
    bool value;

public:
    Boolean();
    Boolean(bool value);
};

#endif //ILANG_BOOLEAN_H
