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

// Von Neumann
word16 VN_X = 1111;

// Mersenne-Twister
struct mt19937p mt;

// AES
u32 Kx[NK], Kex[NB*NR], Px[NB];

// Structure wainting queue
typedef struct file_attente
{
	double* arrivee;
	int taille_arrivee;
	double* depart;
	int taille_depart;
} file_attente;

int rdtsc()
{
    // cette fonction cree un warning : c'est normal.
    __asm__ __volatile__("rdtsc");
}

unsigned long count(unsigned long r, unsigned short size)
{
    unsigned long sum = 0;
	unsigned short i;
    for (i = 0; i < size; ++i)
        sum += ((r >> i) & 1);
    return sum;
}

long sum(unsigned long r, unsigned short size)
{
    return 2*count(r, size) - size;
}

double Frequency(int total, unsigned short size)
{
    return erfc(abs(total)/sqrt(MAX_N*size)/sqrt(2));
}

double Runs(unsigned long tab[MAX_N], unsigned long numOnes, unsigned short size)
{
    double proportion;
    unsigned int compteur, numN, Vobs = 1;
	
    // Pre-test
    proportion = (double) numOnes / (double) (MAX_N*size);
	
    // Test
    if (abs(proportion - 1/2) >= 2/sqrt(MAX_N*size))
        return 0.0;
    
    // Calcul statistique
	for (numN = 0; numN < MAX_N; numN++)
	{
		for (compteur = 0; compteur < size - 1; compteur++) {
			if (((tab[numN] >> compteur) & 1) != ((tab[numN] >> (compteur+1)) & 1)) {
				Vobs++;
			}
		}
		
		// Le premier bit du mot suivant
		if (numN+1 < MAX_N)
		{
			if (((tab[numN] >> compteur) & 1) != ((tab[numN+1] >> (0)) & 1)) {
				Vobs++;
			}
		}
	}
    
    // Calcul Pvaleur
    return erfc(
            abs(Vobs - 2*MAX_N*size*proportion*(1 - proportion)) /
            (2*sqrt(2*MAX_N*size)*proportion*(1 - proportion))
    );
}

void generator_rand_hi(FILE* file, unsigned int n, double result[2])
{
    unsigned int i;
    unsigned int r;
    unsigned long numOnes = 0;
	long convertedSum = 0;
	unsigned long tab[MAX_N];
	
    for (i = 0; i < n; i++)
    {
        r = rand() >> 27;
		tab[i] = r;
		numOnes += count(r, RAND_SIZE);
        convertedSum += sum(r, RAND_SIZE);
        fprintf(file, "%u ", r);
    }
	
	result[0] = Frequency(convertedSum, RAND_SIZE);
	result[1] = Runs(tab, numOnes, RAND_SIZE);
}

void generator_rand_lo(FILE* file, unsigned int n, double result[2])
{
    unsigned int i;
    unsigned int r;
    unsigned long numOnes = 0;
	long convertedSum = 0;
	unsigned long tab[MAX_N];
	
    for (i = 0; i < n; i++)
    {
        r = rand() & 0xF;
		tab[i] = r;
		numOnes += count(r, RAND_SIZE);
        convertedSum += sum(r, RAND_SIZE);
        fprintf(file, "%u ", r);
    }

	result[0] = Frequency(convertedSum, RAND_SIZE);
	result[1] = Runs(tab, numOnes, RAND_SIZE);
}

void generator_von_neumann(FILE* file, unsigned int n, double result[2])
{
    unsigned int i;
    unsigned int r;
    unsigned long numOnes = 0;
	long convertedSum = 0;
	unsigned long tab[MAX_N];
	
    for (i = 0; i < n; i++) {
        r = Von_Neumann(&VN_X);
		tab[i] = r;
		numOnes += count(r, VON_NEUMANN_SIZE);
        convertedSum += sum(r, VON_NEUMANN_SIZE);
        fprintf(file, "%u ", r);
    }
	
	result[0] = Frequency(convertedSum, VON_NEUMANN_SIZE);
	result[1] = Runs(tab, numOnes, VON_NEUMANN_SIZE);
}

void generator_mersenne_twister(FILE* file, unsigned int n, double result[2])
{
    unsigned int i;
    unsigned long r;
    unsigned long numOnes = 0;
	long convertedSum = 0;
	unsigned long tab[MAX_N];

    for (i = 0; i < n; i++) {
        r = genrand(&mt);
		tab[i] = r;
		numOnes += count(r, MERSENNE_TWISTER_SIZE);
        convertedSum += sum(r, MERSENNE_TWISTER_SIZE);
        fprintf(file, "%lu ", r);
    }
	
	result[0] = Frequency(convertedSum, MERSENNE_TWISTER_SIZE);
	result[1] = Runs(tab, numOnes, MERSENNE_TWISTER_SIZE);
}

void generator_aes(FILE* file, unsigned int n, double result[2])
{
    unsigned int i;
    unsigned long r;
    unsigned long numOnes = 0;
	long convertedSum = 0;
	unsigned long tab[MAX_N];
	
    for (i = 0; i < n; i++) {
        r = AES(Px, Kex);
		tab[i] = r;
		numOnes += count(r, AES_SIZE);
        convertedSum += sum(r, AES_SIZE);
        fprintf(file, "%lu ", r);
    }
	
	result[0] = Frequency(convertedSum, AES_SIZE);
	result[1] = Runs(tab, numOnes, AES_SIZE);
}

void init()
{
    // rand()
    srand(rdtsc());
    
	// Von Neumann
	Von_Neumann(&VN_X);
	
    // Mersenne-Twister
    int tmp = rand();
    sgenrand(time(NULL) + tmp, &mt);
    
    // AES
    init_rand(Kx, Px, NK, NB, 45);
    KeyExpansion(Kex, Kx);
}

double Alea()
{
	return AES(Px, Kex) / (pow(2, AES_SIZE)-1);
}

double Exponentielle(double lambda)
{
	return -log(1-Alea())/lambda;
}

file_attente FileMM1(double lambda, double mu, double D)
{
	file_attente resultat = {
		calloc(ARRAY_MAX_SIZE, sizeof(double)), 
		0,
		calloc(ARRAY_MAX_SIZE, sizeof(double)),
		0
	};
	double time = 0.0;
	double t, tA, tD;
	
	while (time < D)
	{
		t = Exponentielle(lambda); // Heure actuelle
		printf(" t: %f", t);
		
		if (resultat.taille_arrivee != 0)
			tA = resultat.arrivee[resultat.taille_arrivee - 1] + t; // Heure d'arrivee
		else
			tA = t;
		resultat.arrivee[resultat.taille_arrivee++] = tA;
		printf(" tA: %f", tA);
		
		// Heure de depart
		if ((resultat.taille_depart == 0) || (tA > resultat.depart[resultat.taille_depart - 1]))
			tD = tA + Exponentielle(mu); // Deja parti
		else
			tD = resultat.depart[resultat.taille_depart - 1] + Exponentielle(mu); // Pas encore parti
		
		resultat.depart[resultat.taille_depart++] = tD;
		printf(" tD: %f", tD);
		
		time += t;
		printf(" time: %f\n", time);
	}
	
	return resultat;
}

/*file_attente FileMM1(double lambda, double mu, double D)
{
	file_attente resultat = {
		calloc(ARRAY_MAX_SIZE, sizeof(double)), 
		0,
		calloc(ARRAY_MAX_SIZE, sizeof(double)),
		0
	};
	double time = 0.0;
	double t, tA, tD;
	
	while (time < D)
	{
		t = Exponentielle(lambda); // Heure actuelle
		printf(" t: %f", t);
		
		if (resultat.taille_arrivee != 0)
			tA = resultat.arrivee[resultat.taille_arrivee - 1] + t; // Heure d'arrivee
		else
			tA = t;
		resultat.arrivee[resultat.taille_arrivee++] = tA;
		printf(" tA: %f", tA);
		time += t;
		printf(" time: %f\n", time);
	}
	
	time = 0.0;
	while (time < D && resultat.taille_depart < resultat.taille_arrivee)
	{
		t = Exponentielle(mu); // Heure actuelle
		printf(" t: %f", t);

		tA = resultat.arrivee[resultat.taille_depart];
	
		// Heure de depart
		if ((resultat.taille_depart == 0) || (tA > resultat.depart[resultat.taille_depart - 1]))
			tD = tA + t; // Deja parti
		else
			tD = resultat.depart[resultat.taille_depart - 1] + t; // Pas encore parti
		
		resultat.depart[resultat.taille_depart++] = tD;
		printf(" tD: %f", tD);
		
		time += t;
		printf(" time: %f\n", time);
	}
	
	return resultat;
}*/

void afficherFileAttente(FILE* fichier, file_attente file, const char* nom)
{
	unsigned int iArrivee = 0;
	unsigned int iDepart = 0;
	unsigned int nbClients = 0;
	
	fprintf(fichier, "evolution_%s_x = zeros(1, %d);\n", nom, file.taille_arrivee + file.taille_depart);
	fprintf(fichier, "evolution_%s_y = zeros(1, %d);\n", nom, file.taille_arrivee + file.taille_depart);
	
	while (iDepart < file.taille_depart)
	{
		if (iArrivee < file.taille_arrivee && file.arrivee[iArrivee] < file.depart[iDepart])
		{
			nbClients++;
			printf("%.2f min.	-> %d clients\n", file.arrivee[iArrivee], nbClients);
			fprintf(fichier, "evolution_%s_x(%d) = %f;\n", nom, 1 + iArrivee + iDepart, file.arrivee[iArrivee]);
			iArrivee++;
		}
		else
		{
			nbClients--;
			printf("%.2f min.	-> %d clients\n", file.depart[iDepart], nbClients);
			fprintf(fichier, "evolution_%s_x(%d) = %f;\n", nom, 1 + iArrivee + iDepart, file.depart[iDepart]);
			iDepart++;
		}
		
		fprintf(fichier, "evolution_%s_y(%d) = %d;\n", nom, iArrivee + iDepart, nbClients);
	}
	
	fprintf(fichier, "\nplot(evolution_%s_x,evolution_%s_y);\n", nom, nom);
}

int main()
{
    unsigned int g, i;
	double result[2];
    
    void (*generators[5]) (FILE* file, unsigned int n, double result[2]) = {
        generator_rand_hi,
        generator_rand_lo,
        generator_von_neumann,
        generator_mersenne_twister,
        generator_aes
    };
    
    FILE* file = fopen(MATLAB_FILENAME, "w");
    
	// Questions 1 - 3
	init();
    for (g = 0; g < NUM_GENERATORS; g++) {
        for (i = 0; i < MAX_I; i++) {
            fprintf(file, "gen_%d_%d = [ ", g, i);
            (*generators[g]) (file, MAX_N, &result);
            fprintf(file, "];\n\n");
            fprintf(file, "p1_%d_%d = %f;\n\n", g, i, result[0]);
            fprintf(file, "p2_%d_%d = %f;\n\n", g, i, result[1]);
        }
		// Total of P1
		fprintf(file, "p1_%d = [ ", g);
		for (i = 0; i < MAX_I; i++)
			fprintf(file, "p1_%d_%d ", g, i);
		fprintf(file, "];\n\n");
		// Total of P2
		fprintf(file, "p2_%d = [ ", g);
		for (i = 0; i < MAX_I; i++)
			fprintf(file, "p2_%d_%d ", g, i);
		fprintf(file, "];\n\n");
    }
	
	// Questions 6 - 7
	file_attente resultat;
	resultat = FileMM1(0.2, 0.33, 180);
	afficherFileAttente(file, resultat, "file_attente_1");
	
    fclose(file);

    return 0;
}
