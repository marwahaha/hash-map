#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "key.h"
#include "kv.h"
#include "value.h"
#include "list.h"
#include "node.h"

#include "hashmap.h"

key* create_k0() {
    const unsigned short l = 4;
    char kb[l] = "abcd";
    unsigned char* k = malloc(sizeof(char)*l);
    memcpy(k, &kb, l);

    return key_new(k, l);
}

key* create_k1() {
    const unsigned short l = 5;
    char kb[l] = "abcde";
    unsigned char* k = malloc(sizeof(char)*l);
    memcpy(k, &kb, l);

    return key_new(k, l);
}

value* create_v0() {
    const unsigned short l = 16;
    char vb[l] = "abcdefghijklmnop";
    unsigned char* v = malloc(sizeof(char)*l);
    memcpy(v, &vb, l);

    return value_new(v, l);
}

value* create_v1() {
    const unsigned short l = 17;
    char vb[l] = "abcdefghijklmnopq";
    unsigned char* v = malloc(sizeof(char)*l);
    memcpy(v, &vb, l);

    return value_new(v, l);
}

kv* create_k0v0() {
    return kv_new(create_k0(), create_v0());
}

kv* create_k0v1() {
    return kv_new(create_k0(), create_v1());
}

kv* create_k1v0() {
    return kv_new(create_k1(), create_v0());
}

kv* create_k1v1() {
    return kv_new(create_k1(), create_v1());
}

void test_internals() {
    printf(" testing internals\n");
    const unsigned short c = 2;
    hashmap* h = hashmap_new_cb(c);
    assert(h != NULL);
    assert(h->c == c);
    for (short i = 0; i < c; i++) {
        assert(h->b[i] != NULL);
        assert(h->b[i]->h == NULL);
    }
    key* k0 = create_k0();
    kv* k0v0 = create_k0v0();
    kv* k0v0D = create_k0v0();
    assert(list_add(h->b[1], k0v0) == NULL);
    assert(kv_compare(list_add(h->b[1], k0v0D), k0v0));
    assert(kv_compare(list_get(h->b[1], k0), k0v0D));
}

void test_simple() {
    printf(" running simple tests\n");
    key* k0 = create_k0();
    kv* k0v0 = create_k0v0();
    kv* k0v0D = create_k0v0();
    hashmap* h = hashmap_new();
    assert(hashmap_add(h, k0v0) == NULL);
    kv* r = hashmap_add(h, k0v0D);
    assert(kv_compare(k0v0, r));
    assert(kv_compare(hashmap_get(h, k0), k0v0));
    assert(kv_compare(hashmap_del(h, k0), k0v0));
    assert(hashmap_get(h, k0) == NULL);
    // best-effort
    free(k0);
    free(k0v0);
    free(k0v0D);
    free(h);
}

void test_count() {
    printf(" testing counts\n");
    key* k0 = create_k0();
    key* k1 = create_k1();
    kv* k0v0 = create_k0v0();
    kv* k1v1 = create_k1v1();
    hashmap* h = hashmap_new();
    assert(_hashmap_count(h) == 0);
    hashmap_add(h, k0v0);
    assert(_hashmap_count(h) == 1);
    hashmap_add(h, k1v1);
    assert(_hashmap_count(h) == 2);
    hashmap_del(h, k0);
    assert(_hashmap_count(h) == 1);
    hashmap_del(h, k1);
    assert(_hashmap_count(h) == 0);
    free(k0);
    free(k1);
    free(k0v0);
    free(k1v1);
    free(h);
}

/*
    since this hashmap allows the storing of random bytes
    generate those and go from there.  re-using the list
    implemented here to store the randomly generated ones
    so reverification can happen

    note that replaces are happening since the key values
    don't change for a given key length (the comparison
    will replace since bytes match, it's key-by-value
    after all)

    since this is developed on mac os x, using arc4random
    and having a little test to error for adding multi-
    platform support later if needed

    also, this function uses the internals of the list
    library (specifically the node struct).  ideally,
    if the node library is re-factored, adding an
    iterator for the list would be ideal, but there's
    a test for that just in case.
*/
#ifndef __APPLE__
#error "fix random support"
#endif
void test_many() {
    printf(" testing many kv pairs\n");
    list* l = list_new();
    hashmap* h = hashmap_new();
    kv* c;
    node* n;
    for (short kl = 1; kl <= 128; kl += 1) {
        unsigned char* kb = malloc(sizeof(char)*kl);
        arc4random_buf(kb, kl);
        for (short vl = 1; vl <= 1024; vl *= 2) {
            unsigned char* vb = malloc(sizeof(char)*vl);
            arc4random_buf(vb, vl);
            kv* kv = kv_new_raw(kb, kl, vb, vl);

            list_add(l, kv);
            hashmap_add(h, kv);

            // check that all previous values are present
            n = l->h;
            while (n != NULL) {
                assert(kv_compare(hashmap_get(h, kv_key(n->kv)), n->kv));
                n = n->n;
            }
        }
    }
    unsigned short t = 0;
    for (unsigned short i = 0; i < h->c; i++) {
        unsigned short c = _list_count(h->b[i]);
        t += c;
        printf("   in bucket %hu, there are %hu keys\n", i, c);
    }
    printf("  in total, there are %hu keys across %hu buckets\n", t, _DEFAULT_BUCKET_COUNT);
}

/*
    FIXME:
        do random deletes and gets on many values
        to see if it errors
*/

int main() {
    printf("testing hashmap.c\n");
    test_internals();
    test_simple();
    test_count();
    test_many();
    return 0;
}
