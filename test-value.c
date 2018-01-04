#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "value.h"

value* create_v0() {
    const unsigned short l = 16;
    char vb[l] = "abcdefghijklmnop";
    unsigned char* v = malloc(sizeof(char)*l);
    memcpy(v, &vb, l);

    return value_new(v, l);
}

value* create_v1() {
    const unsigned short l = 16;
    char vb[l] = "abcdefghijklmnop";
    unsigned char* v = malloc(sizeof(char)*l);
    memcpy(v, &vb, l);

    return value_new(v, l);
}

value* create_v2() {
    const unsigned short l = 17;
    char vb[l] = "abcdefghijklmnopq";
    unsigned char* v = malloc(sizeof(char)*l);
    memcpy(v, &vb, l);

    return value_new(v, l);
}

void test_new() {
    const unsigned short l = 16;
    char vb[l] = "abcdefghijklmnop";
    unsigned char* v = malloc(sizeof(char)*l);
    memcpy(v, &vb, l);

    value* value = value_new(v, l);
    assert(value_l(value) == l);

    unsigned char* vt = value_vb(value);
    char vbt[l];
    memcpy(&vbt, vt, l);
    assert(bcmp(&vbt, &vb, l) == 0);

    free(value->vb);
    free(value);
}

void test_compare() {
    value* v0 = create_v0();
    value* v1 = create_v1();
    value* v2 = create_v2();

    assert(value_compare(v0, v1));
    assert(!value_compare(v1, v2));
    free(v0->vb);
    free(v0);
    free(v1->vb);
    free(v1);
    free(v2->vb);
    free(v2);
}

int main() {
    printf("testing value.c\n");
    test_new();
    test_compare();
    return 0;
}
