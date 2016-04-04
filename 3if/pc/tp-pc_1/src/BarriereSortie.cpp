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
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

//------------------------------------------------------ Include personnel

#include "BarriereSortie.h"
#include "Config.h"
#include "Utils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int semId;
static int shmId;
static pid_t voituriers[NB_PLACES];

//------------------------------------------------------ Fonctions privées

static bool operator > ( requete_t requete1, requete_t requete2 )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    return requete1.usager != AUCUN && (requete2.usager == AUCUN ||
            (requete1.usager == PROF && requete2.usager == AUTRE) ||
            requete1.arrivee < requete2.arrivee);
} //----- fin de operator >

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
        while (waitpid(-1, &status, WNOHANG) > 0)
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
            memoire_partagee_t * mem = AttacherMemoirePartagee(semId, shmId);
            voiture_t voiture = mem->places[place - 1];
            mem->places[place - 1] = PLACE_VIDE;
            mem->placesOccupees--;

            // Traiter les requêtes des barrières
            TypeBarriere barriere = AUCUNE;
            for (size_t i = 0; i < NB_BARRIERES_ENTREE; i++)
            {
                if (barriere == AUCUNE ||
                        mem->requetes[i] > mem->requetes[barriere - 1])
                {
                    barriere = (TypeBarriere) (i + 1);
                }
            }
            if (barriere != AUCUNE)
            {
                Effacer((TypeZone) (REQUETE_R1 + barriere - 1));
                mem->requetes[barriere - 1] = REQUETE_VIDE;
                sembuf autoriser = SEM_BARRIERE_AUTORISER;
                autoriser.sem_num = barriere;
                while (semop(semId, &autoriser, 1) < 0);
            }

            DetacherMemoirePartagee(semId, mem);

            // Afficher les informations de sortie.
            Effacer((TypeZone) (ETAT_P1 + place - 1));
            AfficherSortie(
                    voiture.usager, voiture.numero, voiture.arrivee, time(NULL)
            );
        }
    }
} //----- fin de GererFinVoiturier

static int InitialiserBarriereSortie ( enum TypeBarriere barriere )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    semId = semget(CLE_SEMAPHORE, 1, DROITS);
    shmId = shmget(CLE_MEMOIRE_PARTAGEE, sizeof(memoire_partagee_t), DROITS);

    // Gérer le signal de destruction de la tâche.
    struct sigaction actionDetruire;
    actionDetruire.sa_handler = DetruireBarriereSortie;
    sigemptyset(&actionDetruire.sa_mask);
    actionDetruire.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &actionDetruire, NULL);

    // Gérer le signal de fin d'un voiturier.
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = GererFinVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &actionFinVoiturier, NULL);

    return msgget(CLE_BARRIERES[barriere - 1], DROITS);

} //----- fin de InitialiserBarriereSortie

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void BarriereSortie ( enum TypeBarriere barriere )
// Algorithme :
//
{
    int fileId = InitialiserBarriereSortie(barriere);
    for (;;)
    {
        msg_voiture_t msg;
        pid_t pidVoiturier;
        while (msgrcv(fileId, &msg, MSG_TAILLE, MSG_SORTIE, 0) < 0);
        pidVoiturier = SortirVoiture(msg.place);
        if (pidVoiturier > 0)
        {
            voituriers[msg.place - 1] = pidVoiturier;
        }

    }
} //----- fin de BarriereSortie
