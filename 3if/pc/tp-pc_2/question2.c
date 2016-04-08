#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "primes.h"

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    FILE * file;
    char line[256];
    
    if (argc < 2)
        return 1;
    
    file = fopen(argv[1], "r");
    if (file == NULL)
        return 1;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
        print_prime_factors(atoll(line));
    
    fclose(file);

    return 0;
}
