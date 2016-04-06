/*************************************************************************
             Utils -  Fonctions d'utilité pour l'application
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Utils> (fichier Utils.cpp) -------------
#if ! defined ( UTILS_H )
#define UTILS_H


//------------------------------------------------------------------------
// Rôle du module <Utils>
//
// Fournit quelques fonctions d'utilité utilisées par plusieurs modules.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Config.h"

//------------------------------------------------------------------ Types

//------------------------------------------------------------- Constantes

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
memoire_partagee_t * AttacherMemoirePartagee ( int semId, int shmId );
// Mode d'emploi :
//    <semId> : l'identifiant du mutex
//    <shmId> : l'identifiant de la mémoire partagée
//    Attache la mémoire partagée à ce processus ; bloque tant que le
//    mutex est verrouillé par un autre processus.
//    Renvoie un pointeur vers la mémoire partagée attachée.
//
// Contrat :
//    La mémoire partagée et le mutex doivent avoir été initialisés.

void DetacherMemoirePartagee ( int semId, const memoire_partagee_t * zone );
// Mode d'emploi :
//    <semId> : l'identifiant du mutex
//    <zone> : un pointeur vers la zone de mémoire attachée
//    Détache la mémoire du processus en cours puis déverrouille le mutex.
//    Devrait être appelé après un appel à <AttacherMemoirePartagee>.
//
// Contrat :
//    La mémoire partagée et le mutex doivent avoir été initialisés.

#endif // UTILS_H
