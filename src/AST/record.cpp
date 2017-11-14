#include <vector>

#include "node.h"
#include "record.h"

using std::vector;
using std::pair;
using std::string;

Record::Record(vector<ASTNode*>  *refs): refs(refs) {}