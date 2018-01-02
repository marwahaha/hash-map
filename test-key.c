#include <assert.h>
#include <strings.h>

#include "key.h"

int main() {
    const unsigned short l = 4;
    char kb[l] = "abcd";
    unsigned char* k = (unsigned char*) &kb;

    key* key = key_new(k, l);
    assert(key_h(key) == 2090069583);
    assert(key_l(key) == l);

    unsigned char* kt = key_k(key);
    char kbt[l];
    memcpy(&kbt, kt, l);
    assert(bcmp(kbt, kb, l) == 0);
    
    return 0;
}
