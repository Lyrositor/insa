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
// ID des sémaphores pour toute l'application
// Le sémaphore associé à une barrière a pour indice la valeur numérique
// du <TypeBarriere> correspondant.
static int semId;

// ID de la mémoire partagée
// La mémoire partagée est utilisée par <BarriereSortie> pour décrémenter
// le nombre de places occupées et pour récupérer des informations sur les
// voitures en sortie.
static int shmId;

// Association entre les PID des voituriers en cours et la voiture
// Permet de récupérer l'information sur la voiture qui vient de sortir
// lorsqu'un voiturier termine sa tâche.
static pid_t voituriers[NB_PLACES];

//------------------------------------------------------ Fonctions privées
static bool operator >= ( requete_t r1, requete_t r2 )
// Mode d'emploi :
//    <r1> : la requête de gauche
//    <r2> : la requête de droite
//    Détermine si la <r1> est plus prioritaire ou aussi prioritaire que
//    la <r2>. La <r1> sera prioritaire si un des critères suivants est
//    rempli :
//    - la <r2> est vide
//    - la <r1> a pour usager un <PROF> et la <r2> a pour usager un
//      <AUTRE>
//    - la <r1> a le même usager que la requête <r2> et la requête a été
//      déposée avant
//
// Contrat :
//    Aucun.
//
// Algorithme :
//    Vérifie d'abord que la requête en cours n'est pas vide, puis teste
//    successivement les conditions énoncées ci-dessous.
//
{
    if (r1.usager == AUCUN)
    {
        return false;
    }
    return r2.usager == AUCUN || (r1.usager == PROF && r2.usager == AUTRE) ||
               (r1.usager == r2.usager && r1.arrivee <= r2.arrivee);
} //----- fin de operator >=

static void DetruireBarriereSortie ( int noSignal )
// Mode d'emploi :
//    <noSignal> : le code identifiant le signal reçu
//    Termine proprement la tâche <BarriereSortie>, en supprimant toutes
//    les sous-tâches associées. Le signal reçu doit être <SIGUSR2>.
//    Note : le sémaphore et la file de message associés à cette barrière
//    ne sont PAS supprimés.
//
// Contrat :
//    Doit être appelé lorsque le signal SIGUSR2 a été reçu.
//
// Algorithme :
//    Tue tous les voituriers qui sont encore en train de tourner en leur
//    envoyant <SIGUSR2> ; les processus voituriers sont responsables de
//    la terminaison propre de leurs tâches.
//
{
    if (noSignal == SIGUSR2)
    {
        // Tuer tous les voituriers qui tournent encore
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
//    <noSignal> : le code identifiant le signal reçu
//    Lorsqu'un voiturier a fini de sortir une voiture du Parking,
//    affiche ses informations dans la partie sortie de l'écran, puis
//    supprime les informations sur la voiture et libère la place qu'elle
//    occupait.
//
// Contrat :
//    Doit être appelé lorsqu'une tâche Voiturier a terminé (envoi de
//    <SIGCHLD>).
//
// Algorithme :
//    Comme les signaux ne s'empilent pas, il est possible que cette
//    fonction soit appelée une seule fois alors que plusieurs voituriers
//    ont terminé leur tâche presque en même temps. Conséquemment, la
//    fonction continue à tourner tant qu'il existe des processus fils
//    qui viennent de terminer. Pour chacun d'entre eux, la fonction
//    récupère l'information sur la voiture à partir de la mémoire
//    partagée, vide la place qui était occupée et décrémente le nombre
//    de places occupées.
//    La barrière essaie ensuite de traiter toutes les requêtes en cours,
//    en choisissant celle qui est la plus prioritaire ; cette requête est
//    ensuite effacée et un jeton est déposé dans le sémaphore
//    correspondant à la barrière de la requête pour autoriser le
//    démarrage du voiturier.
//    Finalement, l'affichage est mis à jour.
//
{
    if (noSignal == SIGCHLD)
    {
        int status;
        while (waitpid(-1, &status, WNOHANG) > 0)
        {
            // Vérifier que le processus a bien terminé
            if (!WIFEXITED(status))
            {
                continue;
            }

            // Récupérer le numéro de la place libérée
            int place = WEXITSTATUS(status);
            voituriers[place - 1] = 0;

            // Récupérer les informations sur la voiture qui vient de
            // sortir à partir de la mémoire partagée
            memoire_partagee_t * mem = AttacherMemoirePartagee(semId, shmId);
            voiture_t voiture = mem->places[place - 1];
            mem->places[place - 1] = PLACE_VIDE;
            mem->placesOccupees--;

            // Traiter les requêtes des barrières
            TypeBarriere barriere = AUCUNE;
            for (size_t i = 0; i < NB_BARRIERES_ENTREE; i++)
            {
                if (mem->requetes[i].usager != AUCUN && (
                        barriere == AUCUNE ||
                        mem->requetes[i] >= mem->requetes[barriere - 1]))
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

            // Afficher les informations de sortie
            Effacer((TypeZone) (ETAT_P1 + place - 1));
            AfficherSortie(
                    voiture.usager, voiture.numero, voiture.arrivee, time(NULL)
            );
        }
    }
} //----- fin de GererFinVoiturier

static int InitialiserBarriereSortie ( enum TypeBarriere barriere )
// Mode d'emploi :
//    <barriere> : l'identifiant de la barrière de sortie à gèrer
//    Initialise tous les mécanismes de communication inter-processus pour
//    la barrière spécifiée.
//    Renvoie l'ID de la file de messages spécifique à cette barrière.
//
// Contrat :
//    - la barrière ne doit pas déjà être gérée par un autre processus
//    - les mécanismes IPC pour cette barrière doivent déjà avoir été créés
//    - le comportement est indéterminé en cas de non-respect des contraintes
//
// Algorithme :
//    Les ID de la mémoire partagée et des sémaphores sont récupérés grâce à
//    leurs clés et stockés. Ensuite, les handler pour les signaux <SIGUSR2>
//    et <SIGCHLD> sont mis en place. Finalement, l'ID de la file de messages
//    pour cette barrière est récupéré grâce à sa clé et est renvoyé.
//
{
    semId = semget(CLE_SEMAPHORE, 1, DROITS);
    shmId = shmget(CLE_MEMOIRE_PARTAGEE, sizeof(memoire_partagee_t), DROITS);

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

    return msgget(CLE_BARRIERES[barriere - 1], DROITS);

} //----- fin de InitialiserBarriereSortie

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void BarriereSortie ( enum TypeBarriere barriere )
// Algorithme :
//    Cette fonction tourne à l'infini, attendant la réception de messages
//    dans la file de messages de cette barrière. Lorsqu'un message
//    arrive, il est interprété comme signifiant qu'une voiture essaie de
//    sortir du parking. Un voiturier est alors lancé pour faire sortir la
//    voiture, son PID étant stocké pour réutilisation subséquente.
//    La fonction attend alors la prochaine voiture.
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
