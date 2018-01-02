#include <stdbool.h>

#ifndef VALUE_H
#define VALUE_H

typedef struct value value;
struct value {
    unsigned short l;
    unsigned char* v;
};

/*
    create a new value
*/
value* value_new(unsigned char* v, unsigned short l);

/*
    compares two values
*/
bool value_compare(value* v0, value* v1);

/*
    getters
*/
unsigned short value_l(value* l);
unsigned char* value_v(value* v);

#endif //VALUE_H
