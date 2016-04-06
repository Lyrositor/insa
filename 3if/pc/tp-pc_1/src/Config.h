/*************************************************************************
          Config  -  Fichier de configuration globale du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Config> (fichier Config.h) -------------
#if ! defined ( CONFIG_H )
#define CONFIG_H

//------------------------------------------------------------------------
// Rôle du module <Config>
//
// Fournit des constantes utilisées dans l'ensemble de l'application.
// Ceci inclut les clés des mécanismes IPC, les types utilisés et des
// constantes numériques.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <Outils.h>

//------------------------------------------------------------------ Types
// Représente un message pouvant être stocké dans une file de messages ;
// peut être utilisé pour signifier une entrée ou une sortie.
typedef struct {
    long mtype;          // Type du message
    TypeUsager usager;   // Type de l'usager
    unsigned int numero; // Numéro de voiture (1 - 999)
    unsigned int place;  // Place du parking occupée
} msg_voiture_t;

// Énumère les types de message possibles
enum MsgBarriere {
    MSG_ENTREE = 1, // 1 : Entrée de voiture
    MSG_SORTIE = 2  // 2 : Sortie de voiture
};

// Représente l'information sur une voiture qui est arrivée dans le
// parking. Si la voiture n'a pas encore passé la barrière d'entrée, le
// champ <arrivee> représente le moment où elle est arrivée à la barrière,
// sinon elle représente le moment où elle a passé la barrière.
typedef struct {
    TypeUsager usager;   // Type de l'usager
    unsigned int numero; // Numéro de voiture (1 - 999)
    time_t arrivee;      // Moment d'arrivée de la voiture, soit à la
                         // barrière, soit au passage de la barrière
} voiture_t;

// Représente une requête d'entrée déposée par une voiture en attente
typedef struct {
    TypeUsager usager; // Type de l'usager
    time_t arrivee;    // Moment d'arrivée de la voiture à la barrière
} requete_t;

// Repreésente l'ensemble de la mémoire partagée
typedef struct {
    unsigned int placesOccupees;             // Nombre de places occupées
    voiture_t places[NB_PLACES];             // Détails des places
                                             // occupées
    requete_t requetes[NB_BARRIERES_ENTREE]; // Requêtes déposées
} memoire_partagee_t;

// Énumère les index des sémaphores ; les sémaphores des portes sont
// utilisées pour autoriser l'entrée d'une voiture en attente.
enum SemaphoreBarriere {
    SEM_MUTEX,                     // 0 : le mutex de la mémoire partagée
    SEM_PBP = PROF_BLAISE_PASCAL,  // 1 : la porte Blaise Pascal Prof
    SEM_ABP = AUTRE_BLAISE_PASCAL, // 2 : la porte Blaise Pascal Autre
    SEM_EGB = ENTREE_GASTON_BERGER // 3 : la porte Gaston-Berger
};

//------------------------------------------------------------- Constantes
// Nom de l'exécutable utilisé pour construire les clés
const char * const CHEMIN_IPC = "Parking";

// Permissions sur les mécanismes IPC
const unsigned int DROITS = 0660;

// Numéro minéralogique maximal d'une voiture
const unsigned int MAX_NUM_VOITURE = 999;

// Temps d'attente à une barrière d'entrée après le passage d'une voiture
const unsigned int TEMPO = 1;

// Clés pour les mécanismes IPC
const key_t CLE_BARRIERES[] = {
        ftok(CHEMIN_IPC, 'P'), ftok(CHEMIN_IPC, 'A'), ftok(CHEMIN_IPC, 'E'),
        ftok(CHEMIN_IPC, 'S')
};

// Taille d'un message pour la file de message, sans la longueur du champ
// de type du message
const unsigned int MSG_TAILLE = sizeof(msg_voiture_t) - sizeof(long);

// Clé de la mémoire partagée
const key_t CLE_MEMOIRE_PARTAGEE = ftok(CHEMIN_IPC, 'R');

// Valeur d'une place vide
const voiture_t PLACE_VIDE = {AUCUN, 0, 0};

// Valeur d'une requête vide
const requete_t REQUETE_VIDE = {AUCUN, 0};

// Nombre total de sémaphores
const int NUM_SEMAPHORES = 4;

// Clé des sémaphores
const key_t CLE_SEMAPHORE = ftok(CHEMIN_IPC, 'M');

// Opération de verrouillage du mutex
extern const struct sembuf SEM_MUTEX_VERROUILLER;

// Opération de déverrouillage du mutex
extern const struct sembuf SEM_MUTEX_DEVERROUILLER;

// Demande pour laisser passer une voiture en attente
extern const struct sembuf SEM_BARRIERE_RESERVER;

// Autorisation de la demande de passage de la voiture
extern const struct sembuf SEM_BARRIERE_AUTORISER;

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

#endif // CONFIG_H
