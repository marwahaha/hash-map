#include <stdbool.h>
#include <stdlib.h>
#include <strings.h> //bcmp

#include "../log/log.h"

#include "hash.h"
#include "key.h"

static void _length(unsigned short l) {
    Assert(l > 0, __func__, "key length must be > 0");
    Assert(l <= _MAX_K_LEN, __func__, "key length too large: %hd", l);
}

static void _validate(key* key) {
    Assert(key != NULL, __func__, "key cannot be null");
    Assert(key->l > 0, __func__, "key length > 0");
    Assert(key->h > 0, __func__, "key hash > 0");
    Assert(key->kb != NULL, __func__, "key buffer cannot be null");
}

bool key_compare(key* k0, key* k1) {
    _validate(k0);
    _validate(k1);
    if (k0->h != k1->h) return false;
    else if (k0->l != k1->l) return false;
    else if (bcmp(k0->kb, k1->kb, k0->l)) return false;
    else return true;
}

key* key_new(unsigned char* kb, unsigned short l) {
    _length(l);
    key* key = malloc(sizeof(key));
    Assert(key != NULL, __func__, "malloc error");
    key->kb = kb;
    key->l = l;
    key->h = hash(kb, l);
    _validate(key);
    return key;
}

unsigned int key_h(key* key) {
    _validate(key);
    return key->h;
}

unsigned char* key_kb(key* key) {
    _validate(key);
    return key->kb;
}

unsigned short key_l(key* key) {
    _validate(key);
    return key->l;
}
