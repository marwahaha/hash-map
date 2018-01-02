#include <stdbool.h>

#include "key.h"
#include "value.h"

#ifndef KV_H
#define KV_H

typedef struct kv kv;
struct kv {
    key* k;
    value* v;
};

/*
    create a new key value pair
    returns null if key or value too long
    note that caller must validate k and v pointers are malloc()'d
*/
kv* kv_new(key* k, value* v);
kv* kv_new_raw(unsigned char* k, unsigned short k_len, unsigned char* v, unsigned short v_len);

/*
    compare two kv (by value)
*/
bool kv_compare(kv* kv0, kv* kv1);

/*
    getter functions
*/
key* kv_key(kv* x);
value* kv_value(kv* x);

#endif //KV_H
