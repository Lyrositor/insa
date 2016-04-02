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
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

//------------------------------------------------------ Include personnel
#include "BarriereEntree.h"
#include "Config.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static unsigned int nbVoituriers = 0;
static pid_t voituriers[NB_PLACES];
static int semId;
static int shmId;
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

static void DetruireBarriereEntree ( int noSignal )
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
    if (noSignal == SIGCHLD)
    {
        int status;
        pid_t pid = wait(&status);

        // Vérifier que le processus a bien terminé.
        if (!WIFEXITED(status))
        {
            return;
        }

        int place = WEXITSTATUS(status);
        nbVoituriers--;
        // TODO: Remplacer le tableau des pid des voituriers par une map
        // associant chaque pid à une voiture_t ; quand le voiturier termine,
        // il faut recopier la voiture_t dans la mémoire partagée et la
        // supprimer de la map.

        //AfficherPlace(place, voiture.usager, voiture.numero, voiture.arrivee);
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
    semId = semget(CLE_SEMAPHORE, 1, 0600);
    shmId = shmget(CLE_MEMOIRE_PARTAGEE, sizeof(memoire_partagee_t), 0600);

    // Gérer le signal de destruction de la tâche
    struct sigaction actionDetruire;
    actionDetruire.sa_handler = DetruireBarriereEntree;
    sigemptyset(&actionDetruire.sa_mask);
    actionDetruire.sa_flags = 0;
    sigaction(SIGUSR2, &actionDetruire, NULL);

    // Gérer le signal de fin d'un voiturier
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = GererFinVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = 0;
    sigaction(SIGCHLD, &actionFinVoiturier, NULL);

    // Détermine la boite de message suivant le type de barrière
    return msgget(CLE_BARRIERES[barriere - 1], 0600);
} //----- fin de InitialiserBarriereEntree

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom

void BarriereEntree ( enum TypeBarriere barriere )
// Algorithme :
//
{
    int boite = InitialiserBarriereEntree(barriere);

    for(;;)
    {
        msg_voiture_t msg;

        msgrcv(boite, &msg, sizeof(msg) - sizeof(msg.mtype), MSG_ENTREE, 0);
        DessinerVoitureBarriere(barriere, msg.usager);

        // TODO: S'il n'y a pas de place, écrire la requête dans la mémoire
        // partagée, afficher la requête, enlever un jeton du sémaphore et
        // attendre qu'il soit remis, puis effacer la requête (de
        // l'affichage ; la barrière aura déjà enlevé la requête de la
        // mémoire partagée). Stocker le voiturier dans une map.

        /*voituriers[nbVoituriers] = GarerVoiture(barriere);

        voiture_t voiture;
        voiture.usager = msg.usager;
        voiture.numero = msg.numero;
        voiture.arrivee = time(NULL);
        mem[nbVoituriers] = voiture;

        nbVoituriers++;*/

        sleep(1);
    }
} //----- fin de BarriereEntree

