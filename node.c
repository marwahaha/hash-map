#include <stdlib.h>

#include "../log/log.h"

#include "node.h"
#include "kv.h"

// returns ownership
node* node_new(kv* kv) {
    Assert(kv != NULL, __func__, "kv cannot be null");
    node* n = malloc(sizeof(node));
    Assert(n != NULL, __func__, "malloc error");
    n->n = NULL;
    n->kv = kv;
    return n;
}
