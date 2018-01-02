#include <stdlib.h>

#include "../log/log.h"

#include "list.h"
#include "node.h"
#include "key.h"
#include "kv.h"
#include "value.h"

static void _validate(list* l) {
    Assert(l != NULL, __func__, "list cannot be null");
}

static void _add(list* l, kv* kv) {
    node* n = node_new(kv);
    l->h = n;
}
    
list* list_new(kv* kv) {
    list* l = malloc(sizeof(list));
    Assert(l != NULL, __func__, "malloc error");
    _add(l, kv);
    return l;
}

static kv* _update(node* n, kv* kvN) {
    kv* kvO = n->kv;
    n->kv = kvN;
    return kvO;
}

kv* list_add(list* l, kv* kv) {
    _validate(l);
    if (l->h == NULL) {
        _add(l, kv);
        return NULL;
    }
    else {
        node* n = l->h;
        node* t;
        while (n != NULL) {
            // values match identically
            if (kv_compare(n->kv, kv)) return _update(n, kv);

            key* kN = kv_key(kv);
            key* kO = kv_key(n->kv);
            // keys match, but not values
            if (key_compare(kN, kO)) return _update(n, kv);
            t = n;
            n = n->n;
        }
        t->n = node_new(kv);
        return NULL;
    }
}

kv* list_del(list* l, key* k) {
    _validate(l);
    if (l->h == NULL) return NULL;
    key* key;
    node* n = l->h;
    node* p = NULL;
    while (n != NULL) {
        key = kv_key(n->kv);
        if (key_compare(key, k)) {
            kv* kv = n->kv;
            if (n->n == NULL) {
                if (p == NULL) l->h = NULL;
                else p->n = NULL;
            } else {
                if (p == NULL) l->h = n->n;
                else p->n = n->n;
            }
            free(n);
            return kv;
        }
    }
    return NULL;
}
