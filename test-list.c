#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "key.h"
#include "kv.h"
#include "value.h"
#include "list.h"

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

void test_duplicate() {
    kv* k0v0 = create_k0v0();
    kv* k0v0D = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);
    kv* r = list_add(l, k0v0D);
    assert(kv_compare(k0v0, r));
    assert(k0v0->k == r->k);
    assert(k0v0->v == r->v);
    // best-effort
    free(k0v0);
    free(k0v0D);
    free(l);
}

void test_insert() {
    kv* k0v0 = create_k0v0();
    kv* k0v1 = create_k0v1();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);
    kv* r = list_add(l, k0v1);
    assert(r != NULL);
    assert(kv_compare(k0v0, r));
    assert(!kv_compare(k0v1, r));
    kv* k1v1 = create_k1v1();
    assert(list_add(l, k1v1) == NULL);
    free(k0v0);
    free(k0v1);
    free(k1v1);
    free(l);
}

void test_delete() {
    kv* k0v0 = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);

    kv* k1v1 = create_k1v1();
    assert(list_add(l, k1v1) == NULL);
    key* k0 = create_k0();
    kv* r = list_del(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));
    free(k0v0);
    free(k1v1);
    free(l);
}

void test_get() {
    kv* k0v0 = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);

    kv* k1v1 = create_k1v1();
    assert(list_add(l, k1v1) == NULL);
    key* k0 = create_k0();
    kv* r = list_get(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));
    r = list_get(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));
    free(k0v0);
    free(k1v1);
    free(l);
}

int main() {
    list* l = list_new();
    assert(l != NULL);
    assert(l->h == NULL);
    test_duplicate();
    test_insert();
    test_delete();
    test_get();
    return 0;
}
