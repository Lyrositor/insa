#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "matrix2.h"
#include "matrix9.h"

extern double startTime2, stopTime2, startTime9;

void exercise_1_v1(void* context) {
    struct MATRIX m = *(struct MATRIX*) context;
    int i, j;
    unsigned long sum = 0;
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.cols; j++)
            sum += M(m, i, j);
}

void exercise_1_v2(void* context) {
    struct MATRIX m = *(struct MATRIX*) context;
    int i, j;
    unsigned long sum = 0;
    for (j = 0; j < m.cols; j++)
        for (i = 0; i < m.rows; i++)
            sum += M(m, i, j);
}

void exercise_3_2(char* filename) {
    FILE* fin;
    int** M1;
    int** M2;
    int** M3;
    int m, n;

    fin = fopen(filename, "r");
    fscanf(fin, "%d %d", &m, &n);
    M1 = allocMatrix2(m, n);
    readMatrix2(fin, M1, m, n);
    M2 = allocMatrix2(n, m);
    readMatrix2(fin, M2, n, m);
    fclose(fin);

    M3 = allocMatrix2(m, m);
    startTime2 = clock();
    matrixProd2(M1, M2, M3, m, n);
    stopTime2 = clock();
    printf("%d * %d; SEQUENTIAL; %f secs\n", m, n, (stopTime2-startTime2)/CLOCKS_PER_SEC);
}

void exercise_3_9(char* filename) {
    FILE* fin;
    int** m1;
    int** m2;
    int** m3;
    int m, n;
    double startT, stopT;

    fin = fopen(filename, "r");
    fscanf(fin, "%d %d", &m, &n);
    m1 = makeMatrix9(m, n);
    readMatrix9(fin, m1, m, n);
    m2 = makeMatrix9(n, m);
    readMatrix9(fin, m2, n, m);
    fclose(fin);
    m3 = makeMatrix9(m, m);
    startT = clock();
    matrixProdCole9(m1, m2, m3, m, n, 10);
    stopT = clock();
    printf("%d * %d; SEQUENTIAL; %f secs\n", m, n, (stopT-startT)/CLOCKS_PER_SEC);
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
    char* matrix_file = argv[2];

    // Exercise 1
    /*struct MATRIX m = gen_random_matrix(size);
    printf("Exercise 1 (v1):\n");
    time_func(exercise_1_v1, &m);
    printf("Exercise 1 (v2):\n");
    time_func(exercise_1_v2, &m);*/

    // Exercise 3
    /*printf("Exercise 3 (2):\n");
    exercise_3_2(matrix_file);*/
    printf("Exercise 3 (9):\n");
    exercise_3_9(matrix_file);

    return 0;
}
