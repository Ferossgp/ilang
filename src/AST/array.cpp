#include <vector>

#include "node.h"
#include "array.h"
#include "arrayref.h"

using std::vector;

Array::Array(vector<ArrayRef> *refs): refs(refs) {}