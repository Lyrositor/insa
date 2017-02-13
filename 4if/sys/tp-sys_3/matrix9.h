#ifndef MATRIX9_H
#define MATRIX9_H

void showElapsed9(int id, char m);

int* makeVector9(int n);

int** makeMatrix9(int m, int n);

void readMatrix9(FILE* fin, int** M, int m, int n);

void writeMatrix9(FILE* fout, int** M, int m, int n);

void matrixProdCole9(int** M1, int** M2, int** M3, int m, int n, int z);

void matrixProd9(int** M1, int** M2, int** M3, int m, int n);

#endif // MATRIX9_H
