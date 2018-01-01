#include <assert.h>
#include <stdio.h>

#include "hash.h"

int main() {
    const unsigned int len = 3;
    const char c[len] = "abc";
    const unsigned char* s = (unsigned char*) &c;
    assert(hash(s, len) == 193485963);
    return 0;
}
