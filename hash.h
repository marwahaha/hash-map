#ifndef HASH_H
#define HASH_H

/*
    takes a byte buffer and calculates a hash
    uses djb's hash function

    len is number of bytes (so it's 1-valued, not zero)
*/
unsigned int hash(const unsigned char* s, unsigned int len);

#endif //HASH_H
