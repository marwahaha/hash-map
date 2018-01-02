#include <assert.h>
#include <stdio.h>

#include "hash.h"

int main() {
    const unsigned int l = 3;
    char c[l] = "abc";
    unsigned char* s = (unsigned char*) &c;
    assert(hash(s, l) == 193485963);

    const unsigned int m = 4;
    char d[m] = "abcd";
    unsigned char* t = (unsigned char*) &d;
    assert(hash(t, m) == 2090069583);
    return 0;
}
