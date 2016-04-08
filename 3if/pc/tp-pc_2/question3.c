#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

#include "primes.h"

int main(int argc, char *argv[]) {
    FILE * file;
    char line[MAX_LINE_LENGTH];
    pthread_t calc_thread[MAX_THREADS];
    unsigned int t;
    calc_args_t args;

    if (argc < 2)
        return 1;
    
    file = fopen(argv[1], "r");
    if (file == NULL)
        return 1;

    t = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (t == MAX_THREADS)
            while (t != 0)
                pthread_join(calc_thread[--t], NULL);
        args.n = atoll(line);
        pthread_create(&calc_thread[t++], NULL, calc_task, &args);
    }
    
    fclose(file);

    return 0;
}

