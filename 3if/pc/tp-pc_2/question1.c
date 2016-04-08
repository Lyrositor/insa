#include <stdio.h>
#include <stdint.h>

#include "primes.h"

int main(void) {
    print_prime_factors(77); // expected result:   77: 7 11
    print_prime_factors(84); // expected result:   84: 2 2 3 7

    // expected result:   429496729675917: 3 18229 7853726291
    print_prime_factors(429496729675917);


    return 0;
}
