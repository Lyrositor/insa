#ifndef PRIMES_H
#define PRIMES_H

#include <stdint.h>

typedef struct {
    uint64_t n;
} calc_args_t;

void print_prime_factors(uint64_t n);

#endif
