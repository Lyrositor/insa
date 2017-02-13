#ifndef MATRIX_H
#define MATRIX_H

struct MATRIX {
    int rows;
    int cols;
    int *t;
};

#define M(m, x, y) m.t[x+y*m.cols]

struct MATRIX new_matrix(int cols, int rows);

void print_matrix(struct MATRIX t);

struct MATRIX gen_random_matrix(int size);

#endif // MATRIX_H
