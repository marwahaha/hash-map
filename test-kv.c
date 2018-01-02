#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "key.h"
#include "value.h"
#include "kv.h"

void test_new() {
    const unsigned short k_len = 4;
    const unsigned short v_len = 16;
    char kb[k_len] = "abcd";
    char vb[v_len] = "abcdefghijklmnop";
    unsigned char* k = malloc(sizeof(char)*k_len);
    unsigned char* v = malloc(sizeof(char)*v_len);
    memcpy(k, &kb, k_len);
    memcpy(v, &vb, v_len);

    kv* x = kv_new_raw(k, k_len, v, v_len);

    unsigned char* kt = key_k(kv_key(x));
    char kbt[k_len];
    memcpy(&kbt, kt, k_len);
    assert(bcmp(&kbt, &kb, k_len) == 0);

    unsigned char* vt = value_v(kv_value(x));
    char vbt[v_len];
    memcpy(&vbt, vt, v_len);
    assert(bcmp(&vbt, &vb, v_len) == 0);

    free(k);
    free(v);
    free(x);
}

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

void test_compare() {
    key* k0 = create_k0();
    key* k0D = create_k0();
    key* k1 = create_k1();

    value* v0 = create_v0();
    value* v0D = create_v0();
    value* v1 = create_v1();

    kv* kv0 = kv_new(k0, v0);
    kv* kv0D = kv_new(k0D, v0D);
    kv* kv1 = kv_new(k1, v1);

    assert(kv_compare(kv0, kv0D));
    assert(!kv_compare(kv0, kv1));
}

int main() {
    test_new();
    test_compare();
    return 0;
}
