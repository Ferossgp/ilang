#include "node.h"
#include "recordassign.h"

RecordAssign::RecordAssign(ASTNode *record, ASTNode *ref, ASTNode *value) :
        record(record), ref(ref), value(value) {};
