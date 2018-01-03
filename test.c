#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "key.h"
#include "kv.h"
#include "value.h"

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
    assert(list_add(h->b[1], k0v0D) != NULL);
    assert(kv_compare(list_get(h->b[1], k0), k0v0D));
}

void test_simple() {
    key* k0 = create_k0();
    kv* k0v0 = create_k0v0();
    kv* k0v0D = create_k0v0();
    hashmap* h = hashmap_new();
    assert(hashmap_add(h, k0v0) == NULL);
    kv* r = hashmap_add(h, k0v0D);
    assert(kv_compare(k0v0, r));
    assert(hashmap_get(h, k0) != NULL);
    // best-effort
    free(k0);
    free(k0v0);
    free(k0v0D);
    free(h);
}

int main() {
    test_internals();
    test_simple();
    return 0;
}
