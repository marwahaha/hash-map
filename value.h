#include <stdbool.h>

#ifndef VALUE_H
#define VALUE_H

const static unsigned short _MAX_V_LEN = 1024;

typedef struct value value;
struct value {
    unsigned short l;
    unsigned char* vb;
};

/*
    create a new value
*/
value* value_new(unsigned char* vb, unsigned short l);

/*
    compares two values
*/
bool value_compare(value* v0, value* v1);

/*
    getters
*/
unsigned short value_l(value* l);
unsigned char* value_vb(value* v);

#endif //VALUE_H
