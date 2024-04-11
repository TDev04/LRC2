#include "key.h"
#define BLOCK 8

void encr(unsigned int rounds, unsigned int v[2], unsigned int const key[sizeof(key)]) {
    unsigned int i;
    unsigned int v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;
    for (i = 0; i < rounds; i++)
    {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
    }
    v[0] = v0; v[1] = v1;
}

void decr(unsigned int rounds, unsigned int v[2], unsigned int const key[sizeof(key)]) {
    unsigned int i;
    unsigned int v0 = v[0], v1 = v[1], delta = 0x9E3779B9, sum = delta * rounds;
    for (i = 0; i < rounds; i++)
    {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    }
    v[0] = v0; v[1] = v1;
}