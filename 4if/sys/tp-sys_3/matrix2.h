#ifndef MATRIX2_H
#define MATRIX2_H

void showElapsed2(int id, char* m);

int* allocVector2(int n);

int** allocMatrix2(int m, int n);

void readMatrix2(FILE* fin, int** M, int m, int n);

void writeMatrix2(FILE* fout, int** M, int m, int n);

void matrixProd2(int** M1, int** M2, int** M3, int m, int n);

#endif // MATRIX2_H
