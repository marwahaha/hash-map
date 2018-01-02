#include <stdlib.h>

#include "../log/log.h"

#include "hash.h"
#include "key.h"

static void _validate(key* key) {
    Assert(key != NULL, __func__, "key cannot be null");
    Assert(key->l > 0, __func__, "length > 0");
    Assert(key->h > 0, __func__, "hash > 0");
    Assert(key->k != NULL, __func__, "key buffer cannot be null");
}

key* key_new(unsigned char* kb, unsigned short l) {
    key* key = malloc(sizeof(key));
    Assert(key != NULL, __func__, "malloc error");
    key->k = kb;
    key->l = l;
    key->h = hash(kb, l);
    return key;
}

unsigned int key_h(key* key) {
    _validate(key);
    return key->h;
}

unsigned char* key_k(key* key) {
    _validate(key);
    return key->k;
}

unsigned short key_l(key* key) {
    _validate(key);
    return key->l;
}
