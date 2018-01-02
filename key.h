#include <stdbool.h>

#ifndef KEY_H
#define KEY_H

typedef struct key key;
struct key {
    unsigned char* k;
    unsigned int h;
    unsigned short l;
};

/*
    create a new key
*/
key* key_new(unsigned char* k, unsigned short l);

/*
    compares two keys
*/
bool key_compare(key* k0, key* k1);

/*
    getters
*/
unsigned int key_h(key* key);
unsigned char* key_k(key* key);
unsigned short key_l(key* key);

#endif //KEY_H
