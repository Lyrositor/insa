#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "von_neumann.h"
#include "aes.h"
#include "mersenne_twister.h"

#define ARRAY_MAX_SIZE 1000
#define MATLAB_FILENAME "B3327.m"
#define MAX_I 20
#define MAX_N 1024
#define NUM_GENERATORS 5

// Define the bit sizes of the words for each generator
#define RAND_SIZE 4
#define VON_NEUMANN_SIZE 14
#define MERSENNE_TWISTER_SIZE 32
#define AES_SIZE 32

// Mersenne-Twister
struct mt19937p mt;

// AES
u32 Kx[NK], Kex[NB*NR], Px[NB];

int rdtsc()
{
    // cette fonction cree un warning : c'est normal.
    __asm__ __volatile__("rdtsc");
}

int count(long unsigned int r, unsigned short size)
{
    int sum = 0;
    for (size_t i = 0; i < size; ++i)
        sum += ((r >> i) & 1);
    return sum;
}

int sum(long unsigned int r, unsigned short size)
{
    int c = count(r, size);
    return 2*c - size;
}

double Frequency(int total, unsigned short size)
{
    return erfc(abs(total)/sqrt(MAX_N*size)/sqrt(2));
}

double Runs(long unsigned int r, unsigned short size)
{
    double proportion;
    unsigned int compteur, Vobs = 1;
    // Pre-test
    proportion = (double) count(r, size) / (MAX_N*size);
    
    // Test
    if(abs(proportion - 1/2) >= 2/(MAX_N*size))
        return 0.0;
    
    // Calcul statistique
    for(compteur = 0; compteur < MAX_N*size - 1; compteur++) {
        if(((r >> compteur) & 1) != ((r >> (compteur+1)) & 1)) {
            Vobs += 1;
        }
    }
    
    // Calcul Pvaleur
    return erfc(
            abs(Vobs - 2*MAX_N*size*proportion*(1 - proportion)) /
            (2*sqrt(2*MAX_N*size)*proportion*(1 - proportion))
    );
}

double* generator_rand_hi(FILE* file, unsigned int n)
{
    unsigned int i;
    unsigned int r;
    int total = 0;
    for (i = 0; i < n; i++)
    {
        r = rand() >> 27;
        total += sum(r, RAND_SIZE);
        fprintf(file, "%u ", r);
    }
    return {Frequency(total, RAND_SIZE), Runs(total, RAND_SIZE)};
}

double* generator_rand_lo(FILE* file, unsigned int n)
{
    unsigned int i;
    unsigned int r;
    int total = 0;
    for (i = 0; i < n; i++)
    {
        r = rand() & 0xF;
        total += sum(r, RAND_SIZE);
        fprintf(file, "%u ", r);
    }
    return {Frequency(total, RAND_SIZE), Runs(total, RAND_SIZE)};
}

double* generator_von_neumann(FILE* file, unsigned int n)
{
    unsigned int i;
    unsigned int r;
    int total = 0;
    word16 x = 1111;
    for (i = 0; i < n; i++) {
        r = Von_Neumann(&x);
        total += sum(r, VON_NEUMANN_SIZE);
        fprintf(file, "%u ", r);
    }
    return {Frequency(total, VON_NEUMANN_SIZE), Runs(total, VON_NEUMANN_SIZE)};
}

double* generator_mersenne_twister(FILE* file, unsigned int n)
{
    unsigned int i;
    long unsigned int r;
    int total = 0;
    for (i = 0; i < n; i++) {
        r = genrand(&mt);
        total += sum(r, MERSENNE_TWISTER_SIZE);
        fprintf(file, "%lu ", r);
    }
    return {
            Frequency(total, MERSENNE_TWISTER_SIZE),
            Runs(total, MERSENNE_TWISTER_SIZE)
    };
}

double* generator_aes(FILE* file, unsigned int n)
{
    unsigned int i;
    long unsigned int r;
    int total = 0;
    for (i = 0; i < n; i++) {
        r = AES(Px, Kex);
        total += sum(r, AES_SIZE);
        fprintf(file, "%lu ", r);
    }
    return {Frequency(total, AES_SIZE), Runs(total, AES_SIZE)};
}

void init()
{
    // rand()
    srand(rdtsc());
    
    // Mersenne-Twister
    int tmp = rand();
    sgenrand(time(NULL) + tmp, &mt);
    
    // AES
    init_rand(Kx, Px, NK, NB, 45);
    KeyExpansion(Kex, Kx);
}

int main()
{
    unsigned int g, i;
    double p;
    
    double* (*generators[5]) (FILE* file, unsigned int n) = {
        generator_rand_hi,
        generator_rand_lo,
        generator_von_neumann,
        generator_mersenne_twister,
        generator_aes
    };
    
    FILE* file = fopen(MATLAB_FILENAME, "w");
    
    for (g = 0; g < NUM_GENERATORS; g++) {
        for (i = 0; i < MAX_I; i++) {
            init();
            fprintf(file, "gen_%d_%d = [ ", g, i);
            p = (*generators[g]) (file, MAX_N);
            fprintf(file, "];\n\n");
            fprintf(file, "p1_%d_%d = %f;\n\n", g, i, p[0]);
            fprintf(file, "p2_%d_%d = %f;\n\n", g, i, p[1]);
        }
    }
    
    fclose(file);

    return 0;
}
