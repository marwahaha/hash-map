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
list* list_new();

/*
    returns old kv or null if not a replace
*/
kv* list_add(list* l, kv* kv);

/*
    del a key, returns the kv deleted
*/
kv* list_del(list* l, key* k);

/*
    gets a kv if key exists
*/
kv* list_get(list* l, key* k);

/*
    for unit testing support
*/
unsigned short _list_count(list* l);

#endif //LIST_H
