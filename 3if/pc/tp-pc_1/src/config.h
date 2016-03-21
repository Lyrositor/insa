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

const char * CHEMIN_IPC = "/Parking";
const key_t CLE_BARRIERE_PBP = ftok(CHEMIN_IPC, 'P');
const key_t CLE_BARRIERE_ABP = ftok(CHEMIN_IPC, 'A');
const key_t CLE_BARRIERE_EGB = ftok(CHEMIN_IPC, 'E');
const key_t CLE_BARRIERE_SGB = ftok(CHEMIN_IPC, 'S');

typedef struct msg_voiture {
    long mtype;
    unsigned int numero;
    unsigned int place;
} msg_voiture;

const long MSG_ENTREE_PROF = 0;
const long MSG_ENTREE_AUTRE = 1;
const long MSG_SORTIE = 2;

#endif // CONFIG_H
