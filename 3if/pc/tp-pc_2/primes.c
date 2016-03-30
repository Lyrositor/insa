#include <stdio.h>

#include "primes.h"

#define FIRST_PRIME 2

static void * calc_task(void * arg) {
    calc_args_t args = (calc_args_t) arg;
    print_prime_factors(args.n);
    pthread_exit(0);
}

void print_prime_factors(uint64_t n) {

    uint64_t factor, value;
    
    printf("%llu:", n);
    
    factor = FIRST_PRIME;
    value = n;
    
    while (value != 1) {
        
        if (value % factor == 0) {
            printf(" %llu", factor);
            value = (uint64_t) (value / factor);
        } else
            factor += 1;
        pthread_join(calc_task);
    }
    printf("\n");

}
