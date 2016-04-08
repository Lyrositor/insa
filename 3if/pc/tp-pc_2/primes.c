#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "primes.h"

#define FIRST_PRIME 2
#define SECOND_PRIME 3

#define INC 2

void * calc_task(void * arg) {
    calc_args_t * args = (calc_args_t *) arg;
    print_prime_factors(args->n);
    pthread_exit(0);
}

void * calc_loop_task(void * arg) {
    calc_loop_args_t * args = (calc_loop_args_t *) arg;
    char line[MAX_LINE_LENGTH];

    for (;;) {
        pthread_mutex_lock(&args->mutex);
        if (!fgets(line, MAX_LINE_LENGTH, args->file)) {
            pthread_mutex_unlock(&args->mutex);
            break;
        }
        uint64_t n = atoll(line);
        pthread_mutex_unlock(&args->mutex);
        print_prime_factors(n);
    }

    pthread_exit(0);
}

void * calc_loop_iosync_task(void * arg) {
    calc_loop_iosync_args_t * args = (calc_loop_iosync_args_t *) arg;
    char line[MAX_LINE_LENGTH];

    for (;;) {
        pthread_mutex_lock(&args->file_mutex);
        if (!fgets(line, MAX_LINE_LENGTH, args->file)) {
            pthread_mutex_unlock(&args->file_mutex);
            break;
        }
        uint64_t n = atoll(line);
        pthread_mutex_unlock(&args->file_mutex);
        print_prime_factors_iosync(n, &args->io_mutex);
    }

    pthread_exit(0);
}

void * calc_store_task(void * arg) {
    calc_store_args_t * args = (calc_store_args_t *) arg;
    char line[MAX_LINE_LENGTH];

    for (;;) {
        pthread_mutex_lock(&args->file_mutex);
        if (!fgets(line, MAX_LINE_LENGTH, args->file)) {
            pthread_mutex_unlock(&args->file_mutex);
            break;
        }
        uint64_t n = atoll(line);
        pthread_mutex_unlock(&args->file_mutex);
        print_prime_factors_iosync(n, &args->io_mutex);
    }

    pthread_exit(0);
}

int get_prime_factors(uint64_t n, uint64_t * dest) {
    uint64_t factor, value, k, s;
    
    factor = FIRST_PRIME;
    value = n;
    
    if (value == 1)
        return 0;
    
    while (value % FIRST_PRIME == 0) {
        value /= FIRST_PRIME;
    }

    factor = SECOND_PRIME;
    s = (uint64_t) sqrt(value);
    k = 0;
    while (factor <= s) {
        if (value % factor == 0) {
            dest[k++] = factor;
            value /= factor;
            s = (uint64_t) sqrt(value);
        } else
            factor += INC;
    }
    dest[k++] = n;
    
    return k;
}

void print_prime_factors(uint64_t n) {
    print_prime_factors_iosync(n, NULL);
}

void print_prime_factors_iosync(uint64_t n, pthread_mutex_t * mutex) {
    uint64_t factors[MAX_FACTORS];
    int j, k;
    
    k = get_prime_factors(n, factors);
    
    if (mutex)
        pthread_mutex_lock(mutex);
        
    printf("%ju:", n);
    for (j = 0; j < k; j++)
    {
        printf(" %ju", factors[j]);
    }
    printf("\n");
    
    if (mutex)
        pthread_mutex_unlock(mutex);

}
