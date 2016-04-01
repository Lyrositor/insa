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
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <time.h>

//------------------------------------------------------ Include personnel
#include "BarriereEntree.h"
#include "config.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static size_t nbVoituriers;
static pid_t voituriers[NB_PLACES];
static voiture_t* mem;
static unsigned int compteurVoitures = 0;

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
        
        // Détachement du segment de mémoire partagé
        shmdt(mem);

        exit(0);
    }
} //----- fin de DetruireBarriereEntree

static void GererFinVoiturier(int noSignal)
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
        pid_t pid;
        
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
            // Vérification de fin du processus
            if (!WIFEXITED(status))
            {
                continue;
            }
            
            int place = WEXITSTATUS(status);
            --nbVoituriers;
            voituriers[nbVoituriers] = 0;
            
            voiture_t voiture = mem[nbVoituriers];
            
            AfficherPlace(place, voiture.usager, voiture.numero, voiture.arrivee);
        }
    }
}

static int InitialiserBarriereEntree(enum TypeBarriere barriere)
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

void BarriereEntree(enum TypeBarriere barriere, int shmid)
// Algorithme :
//
{
    int boite = InitialiserBarriereEntree(barriere);
    mem = (voiture_t*) shmat(shmid, NULL, 0);

    for(;;)
    {
        msg_voiture_t msg;
        
        msgrcv(boite, &msg, sizeof(msg) - sizeof(msg.mtype), MSG_ENTREE, 0);
        DessinerVoitureBarriere(barriere, msg.usager);

        voituriers[nbVoituriers] = GarerVoiture(barriere);
        
        voiture_t voiture;
        voiture.usager = msg.usager;
	    voiture.numero = ++compteurVoitures;
    	voiture.arrivee = time(NULL);
        mem[nbVoituriers] = voiture;
        
        nbVoituriers++;
        
        sleep(1);
    }

//    DetruireBarriereEntree();
} //----- fin de BarriereEntree

