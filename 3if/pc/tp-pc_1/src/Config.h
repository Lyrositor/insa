/*************************************************************************
        config  -  Fichier de configuration commun à l'application
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

#if ! defined ( CONFIG_H )
#define CONFIG_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <Outils.h>

const char * const CHEMIN_IPC = "Parking";
const unsigned int DROITS = 0660;
const unsigned int MAX_NUM_VOITURE = 999;
const unsigned int TEMPO = 1;

// Files de messages
typedef struct {
	long mtype; // Type de message
	TypeUsager usager; // Type de l'usager
	unsigned int numero; // Numéro de voiture
	unsigned int place; // Place possédée
} msg_voiture_t;

enum MsgBarriere {
	MSG_ENTREE = 1,
	MSG_SORTIE = 2
};

const key_t CLE_BARRIERES[] = {
		ftok(CHEMIN_IPC, 'P'), ftok(CHEMIN_IPC, 'A'), ftok(CHEMIN_IPC, 'E'),
		ftok(CHEMIN_IPC, 'S')
};
const unsigned int MSG_TAILLE = sizeof(msg_voiture_t) - sizeof(long);

// Mémoire partagée
typedef struct {
	TypeUsager usager;
	unsigned int numero;
	time_t arrivee;
} voiture_t;

typedef struct {
	TypeUsager usager;
	time_t arrivee;
} requete_t;

typedef struct {
	unsigned int placesOccupees;
	voiture_t places[NB_PLACES];
	requete_t requetes[NB_BARRIERES_ENTREE];
} memoire_partagee_t;

const key_t CLE_MEMOIRE_PARTAGEE = ftok(CHEMIN_IPC, 'R');
const voiture_t PLACE_VIDE = {AUCUN, 0, 0};
const requete_t REQUETE_VIDE = {AUCUN, 0};

// Sémaphores
enum SemaphoreBarriere {
	SEM_MUTEX,
	SEM_PBP = PROF_BLAISE_PASCAL,
	SEM_ABP = AUTRE_BLAISE_PASCAL,
	SEM_EGB = ENTREE_GASTON_BERGER
};
const int NUM_SEMAPHORES = 4;
const key_t CLE_SEMAPHORE = ftok(CHEMIN_IPC, 'M');
extern const struct sembuf SEM_MUTEX_VERROUILLER;
extern const struct sembuf SEM_MUTEX_DEVERROUILLER;
extern const struct sembuf SEM_BARRIERE_RESERVER;
extern const struct sembuf SEM_BARRIERE_AUTORISER;

#endif // CONFIG_H
