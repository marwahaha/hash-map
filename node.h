#include "kv.h"

#ifndef NODE_H
#define NODE_H

typedef struct node node;
struct node {
    node* n;
    kv* kv;
};

/*
    creates and returns a node, returns ownership
*/
node* node_new(kv* kv);

#endif //NODE_H
