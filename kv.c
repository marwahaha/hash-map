#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h> // bcmp

#include "../log/log.h"

#include "key.h"
#include "value.h"
#include "kv.h"

static void _validate(kv* x) {
    Assert(x != NULL, __func__, "kv cannot be null");
    Assert(x->k != NULL, __func__, "k cannot be null");
    Assert(x->v != NULL, __func__, "v cannot be null");
}

// return true if k or v too big, false otherwise
static bool _validate_max(const unsigned short kl, const unsigned short vl) {
    Assert(kl > 0 && vl > 0, __func__, "length must be positive");
    if (kl > _MAX_K_LEN || vl > _MAX_V_LEN) return true;
    return false;
}

bool kv_compare(kv* kv0, kv* kv1) {
    key* k0 = kv_key(kv0);
    key* k1 = kv_key(kv1);
    value* v0 = kv_value(kv0);
    value* v1 = kv_value(kv1);
    if (key_compare(k0, k1)) {
        if (value_compare(v0, v1)) {
            return true;
        }
    }
    return false;
}

kv* kv_new(key* k, value* v) {
    Assert(k != NULL && v != NULL, __func__, "key and value must be passed");
    kv* x = malloc(sizeof(kv));
    Assert(x != NULL, __func__, "malloc error");
    x->k = k;
    x->v = v;
    return x;
}

kv* kv_new_raw(unsigned char* kb, unsigned short kl, unsigned char* vb, unsigned short vl) {
    Assert(kb != NULL && vb != NULL, __func__, "key and value must be passed");
    key* k = key_new(kb, kl);
    value* v = value_new(vb, vl);
    return kv_new(k, v);
}

key* kv_key(kv* x) {
    _validate(x);
    return x->k;
}

value* kv_value(kv* x) {
    _validate(x);
    return x->v;
}
