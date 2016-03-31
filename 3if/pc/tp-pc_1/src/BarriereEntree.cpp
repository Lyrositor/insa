/*************************************************************************
         BarriereEntree  -  Gère une barrière d'entrée du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//-- Réalisation de la tâche <BarriereEntree> (fichier BarriereEntree.cpp)

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

//------------------------------------------------------ Include personnel
#include "BarriereEntree.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static size_t nbVoituriers;
static pid_t voituriers[NB_PLACES];

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

static void DetruireBarriereEntree(int noSignal)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    if (noSignal == SIGUSR2)
    {
        // Tuer tous les voituriers qui tournent encore
        for (size_t i = 0; i < nbVoituriers; i++)
        {
            kill(voituriers[i], SIGUSR2);
        }

        exit(0);
    }
} //----- fin de DetruireBarriereEntree

static void GererFinVoiturier ( int noSignal )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    if(noSignal == SIGCHLD)
    {
        int status;
        int place = WEXITSTATUS(status);

        AfficherPlace(place, PROF, 1, time(NULL));

        --nbVoituriers;
    }
}

static int InitialiserBarriereEntree ( enum TypeBarriere barriere )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    // Gérer le signal de destruction de la tâche.
    struct sigaction actionDetruire;
    actionDetruire.sa_handler = DetruireBarriereEntree;
    sigemptyset(&actionDetruire.sa_mask);
    actionDetruire.sa_flags = 0;
    sigaction(SIGUSR2, &actionDetruire, NULL);

    // Gérer le signal de fin d'un voiturier.
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = GererFinVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = 0;
    sigaction(SIGCHLD, &actionFinVoiturier, NULL);

    switch(barriere)
    {
        case PROF_BLAISE_PASCAL:
            return msgget(CLE_BARRIERE_PBP, 0600);
        case AUTRE_BLAISE_PASCAL:
            return msgget(CLE_BARRIERE_ABP, 0600);
        case ENTREE_GASTON_BERGER:
            return msgget(CLE_BARRIERE_EGB, 0600);
        default:
            return 0;
    }
} //----- fin de InitialiserBarriereEntree

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom

void BarriereEntree(enum TypeBarriere barriere)
// Algorithme :
//
{
    int boite = InitialiserBarriereEntree(barriere);

    for(;;)
    {
        msg_voiture_t msg;
        msgrcv(boite, &msg, sizeof(msg) - sizeof(msg.mtype), MSG_ENTREE, 0);
        DessinerVoitureBarriere(barriere, msg.usager);

        voituriers[nbVoituriers++] = GarerVoiture(barriere);
    }

//    DetruireBarriereEntree();
} //----- fin de BarriereEntree

