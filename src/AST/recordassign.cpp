#include "string"
#include "node.h"
#include "recordassign.h"

RecordAssign::RecordAssign(ASTNode *record, std::string ref, ASTNode *value) :
        record(record), ref(ref), value(value) {};
