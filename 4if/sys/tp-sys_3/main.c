#include <stdio.h>
#include <time.h>

#include "matrix.c"

void exercise_1_1_v1(void* context) {
    struct MATRIX m = *(struct MATRIX*) context;
    int i, j;
    unsigned long sum = 0;
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.cols; j++)
            sum += M(m, i, j);
}

void exercise_1_1_v2(void* context) {
    struct MATRIX m = *(struct MATRIX*) context;
    int i, j;
    unsigned long sum = 0;
    for (j = 0; j < m.cols; j++)
        for (i = 0; i < m.rows; i++)
            sum += M(m, i, j);
}

void time_func(void (function)(void* context), void* context) {
    clock_t start = clock(), diff;
    function(context);
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time: %d\n", msec);
}

int main(int argc, char* argv[]) {
    int size = atoi(argv[1]);

    // Exercise 1.1
    struct MATRIX m = gen_random_matrix(size);
    printf("Exercise 1.1 (v1):\n");
    time_func(exercise_1_1_v1, &m);
    printf("Exercise 1.1 (v2):\n");
    time_func(exercise_1_1_v2, &m);

    return 0;
}
