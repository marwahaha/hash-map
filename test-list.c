#include <assert.h>
#include <stdio.h>
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

key* create_k2() {
    const unsigned short l = 6;
    char kb[l] = "abcdef";
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

value* create_v2() {
    const unsigned short l = 18;
    char vb[l] = "abcdefghijklmnopqr";
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

kv* create_k2v2() {
    return kv_new(create_k2(), create_v2());
}

kv* create_k1v0() {
    return kv_new(create_k1(), create_v0());
}

kv* create_k1v1() {
    return kv_new(create_k1(), create_v1());
}

/*
    test.c takes a dependency on the internals
    of the node library, so assert on the 
    dependency
*/
void test_internals() {
    printf("testing internals\n");
    kv* k0v0 = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);
    assert(l->h != NULL);
    assert(l->h->kv != NULL);
    assert(kv_compare(k0v0, l->h->kv));
}

void test_duplicate() {
    printf("testing duplicates\n");
    kv* k0v0 = create_k0v0();
    kv* k0v0D = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);
    kv* r = list_add(l, k0v0D);
    assert(kv_compare(k0v0, r));
    assert(key_compare(kv_key(k0v0), kv_key(r)));
    assert(value_compare(kv_value(k0v0), kv_value(r)));
    // best-effort
    free(k0v0);
    free(k0v0D);
    free(l);
}

void test_insert() {
    printf("testing insert\n");
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

void test_get() {
    printf("testing get\n");
    kv* k0v0 = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);

    kv* k1v1 = create_k1v1();
    assert(list_add(l, k1v1) == NULL);

    kv* k2v2 = create_k2v2();
    assert(list_add(l, k2v2) == NULL);

    key* k0 = create_k0();
    kv* r = list_get(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));

    key* k1 = create_k1();
    r = list_get(l, k1);
    assert(r != NULL);
    assert(kv_compare(r, k1v1));

    key* k2 = create_k2();
    r = list_get(l, k2);
    assert(r != NULL);
    assert(kv_compare(r, k2v2));

    free(k0v0);
    free(k1v1);
    free(k2v2);
    free(l);
}

void test_del_1n_head() {
    printf("testing one node head delete\n");
    kv* k0v0 = create_k0v0();
    list* l = list_new();
    assert(list_add(l, k0v0) == NULL);
    key* k0 = create_k0();
    kv* r = list_del(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));
    assert(l->h == NULL);
    free(k0);
    free(l);
}

list* twoN_list() {
    kv* k0v0 = create_k0v0();
    kv* k1v1 = create_k1v1();
    list* l = list_new();

    assert(list_add(l, k0v0) == NULL);
    key* k0 = create_k0();
    kv* r = list_get(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));

    assert(list_add(l, k1v1) == NULL);
    key* k1 = create_k1();
    r = list_get(l, k1);
    assert(r != NULL);
    assert(kv_compare(r, k1v1));

    return l;
}

void test_del_twoN_head() {
    printf("testing two node head delete\n");
    list* l = twoN_list();
    key* k0 = create_k0();
    kv* r = list_del(l, k0);
    assert(r != NULL);
    kv* k0v0 = create_k0v0();
    assert(kv_compare(r, k0v0));
    kv* k1v1 = create_k1v1();
    assert(kv_compare(l->h->kv, k1v1));
    assert(l->h->n == NULL);
    free(k0);
    free(l);
}

void test_del_twoN_tail() {
    printf("testing two node tail delete\n");
    list* l = twoN_list();
    key* k1 = create_k1();
    kv* r = list_del(l, k1);
    assert(r != NULL);
    kv* k1v1 = create_k1v1();
    assert(kv_compare(r, k1v1));
    kv* k0v0 = create_k0v0();
    assert(kv_compare(l->h->kv, k0v0));
    assert(l->h->n == NULL);
    free(k1);
    free(l);
}

list* threeN_list() {
    kv* k0v0 = create_k0v0();
    kv* k1v1 = create_k1v1();
    kv* k2v2 = create_k2v2();
    list* l = list_new();

    assert(list_add(l, k0v0) == NULL);
    key* k0 = create_k0();
    kv* r = list_get(l, k0);
    assert(r != NULL);
    assert(kv_compare(r, k0v0));

    assert(list_add(l, k1v1) == NULL);
    key* k1 = create_k1();
    r = list_get(l, k1);
    assert(r != NULL);
    assert(kv_compare(r, k1v1));

    assert(list_add(l, k2v2) == NULL);
    key* k2 = create_k2();
    r = list_get(l, k2);
    assert(r != NULL);
    assert(kv_compare(r, k2v2));

    return l;
}

void test_del_threeN_head() {
    printf("testing three node head delete\n");
    list* l = threeN_list();
    key* k0 = create_k0();
    kv* r = list_del(l, k0);
    assert(r != NULL);
    kv* k0v0 = create_k0v0();
    assert(kv_compare(r, k0v0));
    kv* k1v1 = create_k1v1();
    assert(kv_compare(l->h->kv, k1v1));
    kv* k2v2 = create_k2v2();
    assert(kv_compare(l->h->n->kv, k2v2));
    assert(l->h->n->n == NULL);
    free(k0);
    free(l);
}

void test_del_threeN_mid() {
    printf("testing three node mid delete\n");
    list* l = threeN_list();
    key* k1 = create_k1();
    kv* r = list_del(l, k1);
    assert(r != NULL);
    kv* k1v1 = create_k1v1();
    assert(kv_compare(r, k1v1));
    kv* k0v0 = create_k0v0();
    assert(kv_compare(l->h->kv, k0v0));
    kv* k2v2 = create_k2v2();
    assert(kv_compare(l->h->n->kv, k2v2));
    assert(l->h->n->n == NULL);
    free(k1);
    free(l);
}

void test_del_threeN_tail() {
    printf("testing three node tail delete\n");
    list* l = threeN_list();
    key* k2 = create_k2();
    kv* r = list_del(l, k2);
    assert(r != NULL);
    kv* k2v2 = create_k2v2();
    assert(kv_compare(r, k2v2));
    kv* k0v0 = create_k0v0();
    assert(kv_compare(l->h->kv, k0v0));
    kv* k1v1 = create_k1v1();
    assert(kv_compare(l->h->n->kv, k1v1));
    assert(l->h->n->n == NULL);
    free(k2);
    free(l);
}

void test_delete() {
    printf("testing deletes\n");
    test_del_1n_head();

    test_del_twoN_head();
    test_del_twoN_tail();

    test_del_threeN_head();
    test_del_threeN_mid();
    test_del_threeN_tail();
}

void test_count() {
    printf("testing count\n");
    kv* k0v0 = create_k0v0();
    kv* k0v1 = create_k0v1();
    kv* k1v1 = create_k1v1();
    list* l = list_new();
    list_add(l, k0v0);
    assert(_list_count(l) == 1);
    list_add(l, k0v1);
    assert(_list_count(l) == 1);
    list_add(l, k1v1);
    assert(_list_count(l) == 2);
    free(k0v0);
    free(k0v1);
    free(k1v1);
    free(l);
}

int main() {
    list* l = list_new();
    assert(l != NULL);
    assert(l->h == NULL);
    test_internals();
    test_duplicate();
    test_insert();
    test_get();
    test_delete();
    test_count();
    return 0;
}
