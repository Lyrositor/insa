/* matrix9.c - array of arrays */

/*
   Course: Design and Analysis of Parallel Algorithms
   By:     Murray Cole, Edinburgh University
   From:   http://www.inf.ed.ac.uk/teaching/courses/dapa/overheads.pdf
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix9.h"

double startTime2;

void showElapsed9(int id, char m) {
    printf("%d: %s %f secs\n", id, m, (clock()-startTime2)/CLOCKS_PER_SEC);
}

int* makeVector9(int n) {
    return (int *)malloc(n*sizeof(int));
}

int** makeMatrix9(int m, int n) {
    int ** newm = (int **)malloc(m*sizeof(int *));
    int i;
    for (i=0; i<m; i++)
        newm[i] = makeVector9(n);
    return newm;
}

void readMatrix9(FILE* fin, int** M, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            fscanf(fin, "%d", &(M[i][j]));
}

void writeMatrix9(FILE* fout, int** M, int m, int n) {
    int i,j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            fprintf(fout,"%d ",M[i][j]);
        // putc('\n',fout);
    }
}

void matrixProdCole9(int** M1, int** M2, int** M3, int m, int n, int z) {
    int i, j, k, ii, jj, kk, temp;
    int *pa, *pb;

    for (jj = 0; jj < m; jj = jj + z)
        for (kk = 0; kk < n; kk = kk + z)
            for (i = 0; i < m; i++)
                for (j = jj; j < jj + z; j++)
                {
                    pa = &M1[i][kk];
                    pb = &M2[kk][j];
                    temp = (*pa++) * (*pb);
                    for (k = kk + 1; k < kk + z; k++)
                    {
                        pb = pb + m;
                        temp += (*pa++) * (*pb);
                    }
                    M3[i][j] += temp;
                }
}

void matrixProd9(int** M1, int** M2, int** M3, int m, int n) {
    int i, j, k;

    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            M3[i][j] = 0;
            for(k = 0; k < n; k++)
                M3[i][j] = M3[i][j] + M1[i][k] * M2[k][j];
        }
}
