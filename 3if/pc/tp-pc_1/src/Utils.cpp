/*************************************************************************
             Utils -  Fonctions d'utilité pour l'application
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Utils> (fichier Utils.cpp) -----------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/shm.h>

//------------------------------------------------------ Include personnel
#include "Utils.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
memoire_partagee_t * AttacherMemoirePartagee ( int semId, int shmId )
// Algorithme :
//    Verrouille le mutex de la mémoire partagée, puis attache la mémoire
//    partagée à ce processus.
{
    sembuf verrouiller = SEM_MUTEX_VERROUILLER;
    while (semop(semId, &verrouiller, 1) < 0);
    return (memoire_partagee_t *) shmat(shmId, NULL, 0);
}

void DetacherMemoirePartagee ( int semId, const memoire_partagee_t * zone )
// Algorithme :
//    Détache la mémoire partagée de ce processus, puis déverrouille le
//    mutex de la mémoire partagée.
{
    shmdt(zone);
    sembuf deverrouiller = SEM_MUTEX_DEVERROUILLER;
    while (semop(semId, &deverrouiller, 1) < 0);
}
