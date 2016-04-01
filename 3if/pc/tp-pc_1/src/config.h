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
#include <sys/types.h>
#include <Outils.h>

static const char * const CHEMIN_IPC = "/Parking";
static const key_t CLE_BARRIERE_PBP = ftok(CHEMIN_IPC, 'P');
static const key_t CLE_BARRIERE_ABP = ftok(CHEMIN_IPC, 'A');
static const key_t CLE_BARRIERE_EGB = ftok(CHEMIN_IPC, 'E');
static const key_t CLE_BARRIERE_SGB = ftok(CHEMIN_IPC, 'S');

static const key_t CLE_PARKING = ftok(CHEMIN_IPC, 'R');

typedef struct {
    long mtype; // Type de message
    TypeUsager usager; // Type de l'usager
    unsigned int numero; // Numéro de voiture
    unsigned int place; // Place possédée
} msg_voiture_t;

typedef struct {
	TypeUsager usager;
	unsigned int numero;
	time_t arrivee;
} voiture_t;

static const long MSG_ENTREE = 1;
static const long MSG_SORTIE = 2;

#endif // CONFIG_H
