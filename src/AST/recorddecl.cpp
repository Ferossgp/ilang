#include <vector>

#include "node.h"
#include "recorddecl.h"

using std::vector;

RecordDecl::RecordDecl(const vector<ASTNode*> &refs): refs(refs) {
    type = types::Record;
}