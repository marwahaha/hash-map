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
    Assert(count > 0, __func__, "count must be zero or greater");
    hashmap* h = malloc(sizeof(hashmap));
    Assert(h != NULL, __func__, "malloc error");
    h->c = count;
    h->b = malloc(sizeof(list*)*count);
    for (short i = 0; i < count; i++) {
        h->b[i] = list_new();
        Assert(h->b[i] != NULL, __func__, "list allocation error");
        Assert(h->b[i]->h == NULL, __func__, "list allocation error");
    }
    return h;
}

static inline list* _bucket(hashmap* h, key* k) {
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
