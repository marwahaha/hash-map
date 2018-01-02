#include "node.h"
#include "kv.h"

#ifndef LIST_H
#define LIST_H

typedef struct list list;
struct list {
    node* h;
};

/*
    creates a new list, returns ownership
*/
list* list_new(kv* kv);

/*
    returns old kv or null if not a replace
*/
kv* list_add(list* l, kv* kv);

/*
    del a key, returns the kv deleted
*/
kv* list_del(list* l, key* k);

#endif //LIST_H
