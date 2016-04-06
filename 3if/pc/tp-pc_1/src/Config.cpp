/*************************************************************************
          Config  -  Fichier de configuration globale du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Config> (fichier Config.cpp) ---------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Config.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//------------------------------------------------------------- Constantes
const struct sembuf SEM_MUTEX_VERROUILLER = {SEM_MUTEX, -1, 0};
const struct sembuf SEM_MUTEX_DEVERROUILLER = {SEM_MUTEX, 1, 0};
const struct sembuf SEM_BARRIERE_RESERVER = {AUCUNE, -1, 0};
const struct sembuf SEM_BARRIERE_AUTORISER = {AUCUNE, 1, 0};

//---------------------------------------------------- Fonctions publiques
