/*************************************************************************
           BarriereSortie  -  Gère la barrière de sortie du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//-- Réalisation de la tâche <BarriereSortie> (fichier BarriereSortie.cpp)

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

#include <signal.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

//------------------------------------------------------ Include personnel

#include "BarriereSortie.h"
#include "config.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int boiteSGB;
static int shmid;
static pid_t voituriers[NB_PLACES];

//------------------------------------------------------ Fonctions privées

static void DetruireBarriereSortie ( int noSignal )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    if (noSignal == SIGUSR2)
    {
        // Tuer tous les voituriers qui tournent encore.
        for (size_t i = 0; i < NB_PLACES; i++)
        {
            if (voituriers[i])
            {
                kill(voituriers[i], SIGUSR2);
            }
        }

        exit(0);
    }
} //----- fin de DetruireBarriereSortie

static void GererFinVoiturier ( int noSignal )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    if (noSignal == SIGCHLD)
    {
        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
            // Vérifier que le processus a bien terminé.
            if (!WIFEXITED(status))
            {
                continue;
            }
            
            // Récupérer le numéro de la place libérée.
            int place = WEXITSTATUS(status);
            voituriers[place - 1] = 0;
            
            // Récupérer les informations sur la voiture qui vient de
            // sortir à partir de la mémoire partagée.
            voiture_t voiture;
            
            // Afficher les informations de sortie.
            AfficherSortie(
                    voiture.usager, voiture.numero, voiture.arrivee,
                    time(NULL)
            );
        }
    }
} //----- fin de GererFinVoiturier

static void InitialiserBarriereSortie ( int _shmid )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    shmid = _shmid;
    
    // Gérer le signal de destruction de la tâche.
    struct sigaction actionDetruire;
    actionDetruire.sa_handler = DetruireBarriereSortie;
    sigemptyset(&actionDetruire.sa_mask);
    actionDetruire.sa_flags = 0;
    sigaction(SIGUSR2, &actionDetruire, NULL);

    // Gérer le signal de fin d'un voiturier.
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = GererFinVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = 0;
    sigaction(SIGCHLD, &actionFinVoiturier, NULL);

    boiteSGB = msgget(CLE_BARRIERE_SGB, 0600);
} //----- fin de InitialiserBarriereSortie

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void BarriereSortie ( int _shmid )
// Algorithme :
//
{
    InitialiserBarriereSortie(_shmid);
    for (;;)
    {
        msg_voiture_t msg;
        pid_t pidVoiturier;
        msgrcv(boiteSGB, &msg, sizeof(msg) - sizeof(msg.mtype), MSG_SORTIE, 0);
        pidVoiturier = SortirVoiture(msg.place);
        if (pidVoiturier > 0)
        {
            voituriers[msg.place - 1] = pidVoiturier;
        }
        
    }
} //----- fin de BarriereSortie
