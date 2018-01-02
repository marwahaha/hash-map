#include <stdbool.h>

#ifndef KV_H
#define KV_H

typedef struct kv kv;
struct kv {
    unsigned char* k;
    unsigned char* v;
    unsigned short k_len;
    unsigned short v_len;
    unsigned int h;
};

const static unsigned short _MAX_K_LEN = 128;
const static unsigned short _MAX_V_LEN = 1024;

/*
    create a new key value pair
    returns null if key or value too long
    note that caller must validate k and v pointers are malloc()'d
*/
kv* kv_new(unsigned char* k, unsigned short k_len, unsigned char* v, unsigned short v_len);

/*
    compare two kv (by value)
*/
bool kv_compare(kv* kv0, kv* kv1);

/*
    getter functions
*/
unsigned int kv_h(kv* x);
unsigned char* kv_k(kv* x);
unsigned char* kv_v(kv* x);
unsigned short kv_k_len(kv* x);
unsigned short kv_v_len(kv* x);

#endif //KV_H
