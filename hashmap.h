#include "key.h"
#include "kv.h"
#include "list.h"

#ifndef HASHMAP_H
#define HASHMAP_H

const static unsigned short _DEFAULT_BUCKET_COUNT = 16;

typedef struct hashmap hashmap;
struct hashmap {
    list** b;
    unsigned short c;
};

// create a new hashmap w/ default bucket count
hashmap* hashmap_new();
// using custom bucket count
hashmap* hashmap_new_cb(unsigned short count);

// self-explanatory
kv* hashmap_add(hashmap* h, kv* kv);
kv* hashmap_del(hashmap* h, key* k);
kv* hashmap_get(hashmap* h, key* k);

// for unit test
unsigned short _hashmap_count(hashmap* h);

#endif //HASH_MAP_H
