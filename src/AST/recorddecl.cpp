#include <vector>

#include "node.h"
#include "recorddecl.h"

using std::vector;
using std::pair;
using std::string;

RecordDecl::RecordDecl(vector<ASTNode*>  *refs): refs(refs) {}