#include <stdbool.h>
#include <stdlib.h>
#include <strings.h> //bcmp

#include "../log/log.h"

#include "value.h"

static void _validate(value* value) {
    Assert(value != NULL, __func__, "value cannot be null");
    Assert(value->l > 0, __func__, "length > 0");
    Assert(value->v != NULL, __func__, "value buffer cannot be null");
}

bool value_compare(value* v0, value* v1) {
    _validate(v0);
    _validate(v1);
    if (v0->l != v1->l) return false;
    else if (bcmp(v0->v, v1->v, v0->l)) return false;
    else return true;
}

value* value_new(unsigned char* vb, unsigned short l) {
    value* value = malloc(sizeof(value));
    Assert(value != NULL, __func__, "malloc error");
    value->v = vb;
    value->l = l;
    return value;
}

unsigned char* value_v(value* value) {
    _validate(value);
    return value->v;
}

unsigned short value_l(value* value) {
    _validate(value);
    return value->l;
}
