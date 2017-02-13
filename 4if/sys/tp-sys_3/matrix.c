#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct MATRIX new_matrix(int cols, int rows) {
    struct MATRIX t;
    t.rows=rows;
    t.cols=cols;
    t.t = (int*) malloc(sizeof(int)*cols*rows);
    return t;
}

void print_matrix(struct MATRIX t) {
    int i, j;
    for(i = 0; i < t.rows; i++) {
        printf("| ");
        for(j=0; j < t.cols; j++) {
            printf("%d ", M(t, j, i));
            printf("|\n");
        }
        printf("\n");
    }
}

struct MATRIX gen_random_matrix(int size) {
    int i, j;
    struct MATRIX m = new_matrix(size, size);
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            M(m, i, j) = rand();
    return m;
}
