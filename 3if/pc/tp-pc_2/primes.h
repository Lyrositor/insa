#ifndef PRIMES_H
#define PRIMES_H

#include <pthread.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 256
#define MAX_FACTORS 64
#define MAX_THREADS 2
#define NB_FACTORISATIONS 1000000

typedef struct {
    uint64_t n;
} calc_args_t;

typedef struct {
    FILE * file;
    pthread_mutex_t mutex;
} calc_loop_args_t;

typedef struct {
    FILE * file;
    pthread_mutex_t file_mutex;
    pthread_mutex_t io_mutex;
} calc_loop_iosync_args_t;

typedef struct {
    FILE * file;
    uint64_t factors[NB_FACTORISATIONS][MAX_FACTORS];
    pthread_mutex_t file_mutex;
    pthread_mutex_t io_mutex;
    pthread_mutex_t shm_mutex;
} calc_store_args_t;

void * calc_task(void * arg);
void * calc_loop_task(void * arg);
void * calc_loop_iosync_task(void * arg);
void * calc_store_task(void * arg);
int get_prime_factors(uint64_t n, uint64_t * dest);
void print_prime_factors(uint64_t n);
void print_prime_factors_iosync(uint64_t n, pthread_mutex_t * mutex);

#endif
