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
#include <map>
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
#include "Utils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int semId;
static int shmId;
static map<pid_t, voiture_t> voituriers;

//------------------------------------------------------ Fonctions privées
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
        // Tuer tous les voituriers qui tournent encore
        map<pid_t, voiture_t>::iterator it;
        for (it = voituriers.begin(); it != voituriers.end(); it++)
        {
            kill(it->first, SIGUSR2);
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
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
            // Vérifier que le processus a bien terminé.
            if (!WIFEXITED(status))
            {
                continue;
            }

            // Récupérer le numéro de la place occupée et trouver la voiture
            // qui vient de se garer.
            unsigned int place = (unsigned int) WEXITSTATUS(status);
            voiture_t voiture = voituriers.find(pid)->second;

            memoire_partagee_t * mem = AttacherMemoirePartagee(semId, shmId);
            mem->places[place - 1] = voiture;
            DetacherMemoirePartagee(semId, mem);
            voituriers.erase(pid);

            AfficherPlace(place, voiture.usager, voiture.numero, voiture.arrivee);
        }
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
    semId = semget(CLE_SEMAPHORE, 1, DROITS);
    shmId = shmget(CLE_MEMOIRE_PARTAGEE, sizeof(memoire_partagee_t), DROITS);

    // Gérer le signal de destruction de la tâche
    struct sigaction actionDetruire;
    actionDetruire.sa_handler = DetruireBarriereEntree;
    sigemptyset(&actionDetruire.sa_mask);
    actionDetruire.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &actionDetruire, NULL);

    // Gérer le signal de fin d'un voiturier
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = GererFinVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &actionFinVoiturier, NULL);

    // Détermine la boite de message suivant le type de barrière
    return msgget(CLE_BARRIERES[barriere - 1], DROITS);
} //----- fin de InitialiserBarriereEntree

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void BarriereEntree ( enum TypeBarriere barriere )
// Algorithme :
//
{
    int fileId = InitialiserBarriereEntree(barriere);

    for (;;)
    {
        msg_voiture_t msg;
        while (msgrcv(fileId, &msg, MSG_TAILLE, MSG_ENTREE, 0) < 0);

        voiture_t voiture = {msg.usager, msg.numero, time(NULL)};
        DessinerVoitureBarriere(barriere, voiture.usager);

        memoire_partagee_t * mem = AttacherMemoirePartagee(semId, shmId);
        bool voituresEnAttente = false;
        for (size_t i = 0; i < NB_BARRIERES_ENTREE; i++)
        {
            if (mem->requetes[i].usager != AUCUN)
            {
                voituresEnAttente = true;
                break;
            }
        }
        if (mem->placesOccupees == NB_PLACES || voituresEnAttente)
        {
            requete_t requete;
            requete.usager = voiture.usager;
            requete.arrivee = voiture.arrivee;
            mem->requetes[barriere] = requete;
            DetacherMemoirePartagee(semId, mem);
            AfficherRequete(barriere, requete.usager, time(NULL));

            sembuf reserver = SEM_BARRIERE_RESERVER;
            reserver.sem_num = barriere;
            while (semop(semId, &reserver, 1) < 0);
            mem = AttacherMemoirePartagee(semId, shmId);
        }
        mem->placesOccupees++;
        DetacherMemoirePartagee(semId, mem);

        pid_t voiturier = GarerVoiture(barriere);
        voituriers[voiturier] = voiture;

        sleep(TEMPO);
    }
} //----- fin de BarriereEntree

