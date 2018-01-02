#include <assert.h>
#include <string.h>

#include "kv.h"

kv* create_kv0() {
    const unsigned short k_len = 4;
    const unsigned short v_len = 16;
    char kb[k_len] = "abcd";
    char vb[v_len] = "abcdefghijklmnop";
    unsigned char* k = (unsigned char*) &kb;
    unsigned char* v = (unsigned char*) &vb;

    return kv_new(k, k_len, v, v_len);
}

kv* create_kv1() {
    const unsigned short k_len = 4;
    const unsigned short v_len = 16;
    char kb[k_len] = "abcd";
    char vb[v_len] = "abcdefghijklmnop";
    unsigned char* k = (unsigned char*) &kb;
    unsigned char* v = (unsigned char*) &vb;

    return kv_new(k, k_len, v, v_len);
}

kv* create_kv2() {
    const unsigned short k_len = 5;
    const unsigned short v_len = 17;
    char kb[k_len] = "abcde";
    char vb[v_len] = "abcdefghijklmnopq";
    unsigned char* k = (unsigned char*) &kb;
    unsigned char* v = (unsigned char*) &vb;

    return kv_new(k, k_len, v, v_len);
}

void test_new() {
    const unsigned short k_len = 4;
    const unsigned short v_len = 16;
    char kb[k_len] = "abcd";
    char vb[v_len] = "abcdefghijklmnop";
    unsigned char* k = (unsigned char*) &kb;
    unsigned char* v = (unsigned char*) &vb;

    kv* x = kv_new(k, k_len, v, v_len);
    assert(kv_h(x) == 2090069583);
    assert(kv_k_len(x) == k_len);
    assert(kv_v_len(x) == v_len);

    unsigned char* kt = kv_k(x);
    char kbt[k_len];
    memcpy(&kbt, kt, k_len);
    assert(bcmp(&kbt, &kb, k_len) == 0);

    unsigned char* vt = kv_v(x);
    char vbt[v_len];
    memcpy(&vbt, vt, v_len);
    assert(bcmp(&vbt, &vb, v_len) == 0);
}

void test_compare() {
    kv* kv0 = create_kv0();
    kv* kv1 = create_kv1();
    assert(kv_compare(kv0, kv1));
    kv* kv2 = create_kv2();
    assert(!kv_compare(kv0, kv2));
}

int main() {
    test_new();
    test_compare();
    return 0;
}
