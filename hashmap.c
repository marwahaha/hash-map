#include <stdlib.h>

#include "../log/log.h"

#include "key.h"
#include "kv.h"
#include "list.h"
#include "hashmap.h"

hashmap* hashmap_new() {
    return hashmap_new_cb(_DEFAULT_BUCKET_COUNT);
}

hashmap* hashmap_new_cb(unsigned short count) {
    Assert(count > 0, __func__, "count must be > zero");
    hashmap* h = malloc(sizeof(hashmap));
    Assert(h != NULL, __func__, "malloc error");
    h->c = count;
    h->b = malloc(sizeof(list*)*count);
    for (short i = 0; i < count; i++) {
        h->b[i] = list_new();
    }
    return h;
}

static inline void _validate(hashmap* h) {
    Assert(h != NULL, __func__, "hashmap cannot be null");
    Assert(h->c > 0, __func__, "problem with c");
    Assert(h->b != NULL, __func__, "problem with b");
}

static inline list* _bucket(hashmap* h, key* k) {
    _validate(h);
    return h->b[ key_h(k) % h->c ];
}

kv* hashmap_add(hashmap* h, kv* kv) {
    return list_add(_bucket(h, kv_key(kv)), kv);
}

kv* hashmap_del(hashmap* h, key* k) {
    return list_del(_bucket(h, k), k);
}

kv* hashmap_get(hashmap* h, key* k) {
    return list_get(_bucket(h, k), k);
}

void _hashmap_free(hashmap* h) {
    for (short i = 0; i < h->c; i++) {
        free(h->b[i]);
    }
    free(h);
}

unsigned short _hashmap_count(hashmap* h) {
    _validate(h);
    unsigned short count = 0;
    for (short i = 0; i < h->c; i++) {
        count += _list_count(h->b[i]);
    }
    return count;
}
