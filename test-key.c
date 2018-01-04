#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "key.h"

key* create_k0() {
    const unsigned short l = 4;
    char kb[l] = "abcd";
    unsigned char* k = malloc(sizeof(char)*l);
    memcpy(k, &kb, l);

    return key_new(k, l);
}

key* create_k1() {
    const unsigned short l = 4;
    char kb[l] = "abcd";
    unsigned char* k = malloc(sizeof(char)*l);
    memcpy(k, &kb, l);

    return key_new(k, l);
}

key* create_k2() {
    const unsigned short l = 5;
    char kb[l] = "abcde";
    unsigned char* k = malloc(sizeof(char)*l);
    memcpy(k, &kb, l);

    return key_new(k, l);
}

void test_new() {
    const unsigned short l = 4;
    char kb[l] = "abcd";
    unsigned char* k = malloc(sizeof(char)*l);
    memcpy(k, &kb, l);

    key* key = key_new(k, l);
    assert(key_h(key) == 2090069583);
    assert(key_l(key) == l);

    unsigned char* kt = key_kb(key);
    char kbt[l];
    memcpy(&kbt, kt, l);
    assert(bcmp(&kbt, &kb, l) == 0);

    free(key->kb);
    free(key);
}

void test_compare() {
    key* k0 = create_k0();
    key* k1 = create_k1();
    key* k2 = create_k2();

    assert(key_compare(k0, k1));
    assert(!key_compare(k1, k2));
    free(k0->kb);
    free(k0);
    free(k1->kb);
    free(k1);
    free(k2->kb);
    free(k2);
}

int main() {
    test_new();
    test_compare();
    return 0;
}
