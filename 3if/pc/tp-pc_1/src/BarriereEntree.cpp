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
#include <map>

//------------------------------------------------------ Include personnel
#include "BarriereEntree.h"
#include "Config.h"
#include "Utils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static unsigned int nbVoituriers = 0;
static map<pid_t, voiture_t> voituriers;
static int semId;
static int shmId;

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
        // Tuer tous les voituriers qui tournent encore
        map<pid_t, voiture_t>::iterator it;
        for(it = voituriers.begin(); it != voituriers.end(); it++)
        {
            kill(it->first, SIGUSR2);
        }
        
        // Attendre que les voituriers aient bien terminé
        for(it = voituriers.begin(); it != voituriers.end(); it++)
        {
            waitpid(it->first, NULL, 0);
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

        /*// Vérifier que le processus a bien terminé
        while (!WIFEXITED(status))
        {
        }*/

        int place = WEXITSTATUS(status);
        
        // TODO: Remplacer le tableau des pid des voituriers par une map
        // associant chaque pid à une voiture_t ; quand le voiturier termine,
        // il faut recopier la voiture_t dans la mémoire partagée et la
        // supprimer de la map
        
        voiture_t voiture = voituriers.find(pid)->second;

        memoire_partagee_t* mem = AttacherMemoirePartagee(shmId, semId); // /!\ BUG -> Ne passe jamais cette ligne
        mem->places[place - 1] = voiture;

        DetacherMemoirePartagee(semId, mem);
        voituriers.erase(pid);

        AfficherPlace(place, voiture.usager, voiture.numero, voiture.arrivee);
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
    actionDetruire.sa_flags = 0;
    sigaction(SIGUSR2, &actionDetruire, NULL);

    // Gérer le signal de fin d'un voiturier
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = GererFinVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = 0;
    sigaction(SIGCHLD, &actionFinVoiturier, NULL);

    // Détermine la boite de message suivant le type de barrière
    return msgget(CLE_BARRIERES[barriere - 1], DROITS);
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
        
        /*memoire_partagee_t* mem = AttacherMemoirePartagee(shmId, semId);
        bool isRequete = true;
        for(int i = 0; i < NB_PLACES; i++)
        {
            if(&mem->places[i] == &PLACE_VIDE)
            {
                isRequete = false;
            }
        }*/
        
        voiture_t voiture;
        voiture.usager = msg.usager;
        voiture.numero = msg.numero;
        voiture.arrivee = time(NULL);
        
        /*// Pas de place disponible : requete !
        if(isRequete == true)
        {
            requete_t requete;
            requete.usager = voiture.usager;
            requete.arrivee = voiture.arrivee;
            mem->requetes[barriere] = requete;
            DetacherMemoirePartagee(semId, mem);
            
            sembuf verrouiller = SEM_BARRIERE_RESERVER;
            AfficherRequete(barriere, msg.usager, time(NULL));
            while (semop(semId, &verrouiller, 1) < 0);
            switch(barriere)
            {
                case PROF_BLAISE_PASCAL:
                    Effacer(REQUETE_R1);
                    break;
                case AUTRE_BLAISE_PASCAL:
                    Effacer(REQUETE_R2);
                    break;
                case ENTREE_GASTON_BERGER:
                    Effacer(REQUETE_R3);
                    break;
                default:
                   break;
            }
        }
        else
        {
            DetacherMemoirePartagee(semId, mem);
        }*/

        pid_t voiturier = GarerVoiture(barriere);
        
        voituriers.insert(pair<pid_t, voiture_t>(voiturier, voiture));

        sleep(1);
    }
} //----- fin de BarriereEntree

