#include "hash.h"

unsigned int hash(const unsigned char* s, unsigned int len) {
    unsigned int hash = 5381;
    for (unsigned int i = 0; i < len; s++, i++) {
        hash = ((hash << 5) + hash) + (*s);
    }
    return hash;
}
