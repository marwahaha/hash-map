#include <assert.h>
#include <string.h>

#include "kv.h"

int main() {
    const unsigned int k_len = 4;
    const unsigned int v_len = 16;
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

    return 0;
}
