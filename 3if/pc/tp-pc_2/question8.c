#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "primes.h"

int main(int argc, char *argv[]) {
    pthread_t calc_thread[MAX_THREADS];
    unsigned int t;
    calc_loop_iosync_args_t args;

    if (argc < 2)
        return 1;

    args.file = fopen(argv[1], "r");
    if (args.file == NULL)
        return 1;
    pthread_mutex_init(&args.file_mutex, NULL);
    pthread_mutex_init(&args.io_mutex, NULL);
    
    for (t = 0; t < MAX_THREADS; t++)
        pthread_create(&calc_thread[t], NULL, calc_loop_iosync_task, &args);
    for (t = 0; t < MAX_THREADS; t++)
        pthread_join(calc_thread[t], NULL);
        
    fclose(args.file);

    return 0;
}

