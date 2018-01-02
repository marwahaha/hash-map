#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../log/log.h"

#include "hash.h"
#include "kv.h"

static void _validate_kv(kv* x) {
    Assert(x != NULL, __func__, "kv cannot be null");
    Assert(x->k != NULL, __func__, "k cannot be null");
    Assert(x->v != NULL, __func__, "v cannot be null");
    Assert(x->k_len > 0 && x->v_len > 0, __func__, "length must be positive");
}

// return true if k or v too big, false otherwise
static bool _validate_max(const unsigned short k_len, const unsigned short v_len) {
    Assert(k_len > 0 && v_len > 0, __func__, "length must be positive");
    if (k_len > _MAX_K_LEN || v_len > _MAX_V_LEN) return true;
    return false;
}

kv* kv_new(unsigned char* k, unsigned short k_len, unsigned char* v, unsigned short v_len) {
    Assert(k != NULL && v != NULL, __func__, "key and value must be passed");
    if (_validate_max(k_len, v_len)) return NULL;
    kv* x = malloc(sizeof(kv));
    Assert(x != NULL, __func__, "malloc error");
    x->k = k;
    x->v = v;
    x->k_len = k_len;
    x->v_len = v_len;
    x->h = hash(k, k_len);
    return x;
}

unsigned int kv_h(kv* x) {
    _validate_kv(x);
    return x->h;
}

unsigned char* kv_k(kv* x) {
    _validate_kv(x);
    return x->k;
}

unsigned char* kv_v(kv* x) {
    _validate_kv(x);
    return x->v;
}

unsigned short kv_k_len(kv* x) {
    _validate_kv(x);
    return x->k_len;
}

unsigned short kv_v_len(kv* x) {
    _validate_kv(x);
    return x->v_len;
}
