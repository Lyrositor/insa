/*
   matrix2.c - Matrix Multiplication
               matrix stored as array of vectors
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double startTime2, stopTime2;

/* Timing ------------------------------------------------------- */
void showElapsed2(int id, char* m) {
    printf("%d: %s %f secs\n", id, m, (clock()-startTime2)/CLOCKS_PER_SEC);
}

/* Aux fcts ------------------------------------------------------- */
int* allocVector2(int n) {
    return (int*) malloc(n*sizeof(int));
}

int** allocMatrix2(int m, int n) {
    int** newM = (int**) malloc(m*sizeof(int*));
    int i;
    for (i = 0; i < m; i++)
        newM[i] = allocVector2(n);
    return newM;
}

/* read a matrix M, with m rows and n columns, from a stream fin */
void readMatrix2(FILE* fin, int** M, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++)   /* iterate over all rows */
        for (j = 0; j < n; j++) /* iterate over all columns */
            fscanf(fin, "%d", &(M[i][j]));  /* read data */
}

/* write a matrix M, with m rows and n columns, to a stream fout */
void writeMatrix2(FILE* fout, int** M, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {    /* iterate over all rows */
        for (j = 0; j < n; j++)  /* iterate over all columns */
            fprintf(fout, "%d ", M[i][j]); /* write data */
        putc('\n', fout);
    }
}

/* matrix product of M1 (m row, n columns) with M2, with result in M3 */
void matrixProd2(int** M1, int** M2, int** M3, int m, int n) {
    int i, j, k;

    for (i = 0; i < m; i++)  /* iterate over all rows */
        for (j = 0; j < m; j++) { /* iterate over all columns */
            M3[i][j] = 0;
            for (k = 0; k < n; k++) /* compute dot product */
                M3[i][j] = M3[i][j] + M1[i][k] * M2[k][j];
        }
}
