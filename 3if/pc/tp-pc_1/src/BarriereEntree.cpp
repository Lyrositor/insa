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
// ID des sémaphores pour toute l'application
// Le sémaphore associé à une barrière a pour indice la valeur numérique
// du <TypeBarriere> correspondant.
static int semId;

// ID de la mémoire partagée
// La mémoire partagée est utilisée par <BarriereEntree> pour vérifier
// si certaines places sont encore disponibles et pour stocker les
// informations sur les voitures qui se garent.
static int shmId;

// Association entre les PID des voituriers en cours et la voiture
// Permet de récupérer l'information sur la voiture qui vient de se
// garer lorsqu'un voiturier termine sa tâche.
static map<pid_t, voiture_t> voituriers;

//------------------------------------------------------ Fonctions privées
static void DetruireBarriereEntree ( int noSignal )
// Mode d'emploi :
//    <noSignal> : le code identifiant le signal reçu
//    Termine proprement la tâche <BarriereEntree>, en supprimant toutes
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
        for (map<pid_t, voiture_t>::iterator it = voituriers.begin(); it != voituriers.end(); it++)
        {
            kill(it->first, SIGUSR2);
        }

        exit(0);
    }
} //----- fin de DetruireBarriereEntree

static void GererFinVoiturier ( int noSignal )
// Mode d'emploi :
//    <noSignal> : le code identifiant le signal reçu
//    Lorsqu'un voiturier a fini de garer une voiture entrée par cette
//    barrière, enregistre le nouvel emplacement de la voiture et affiche
//    ses détails à l'écran. Le signal reçu doit être SIGCHLD.
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
//    récupère les informations sur la voiture qui vient de se garer, les
//    copie dans la mémoire partagée pour utilisation subséquente par la
//    barrière de sortie puis affiche les détails à l'écran. Le PID du
//    voiturier est alors effacé.
//
{
    if (noSignal == SIGCHLD)
    {
        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
            // Vérifier que le processus a bien terminé
            if (!WIFEXITED(status))
            {
                continue;
            }

            // Récupérer le numéro de la place occupée et trouver la
            // voiture qui vient de se garer
            unsigned int place = (unsigned int) WEXITSTATUS(status);
            voiture_t voiture = voituriers.find(pid)->second;

            // Enregistrer l'information sur la voiture qui vient de se
            // garer
            memoire_partagee_t * mem = AttacherMemoirePartagee(semId, shmId);
            mem->places[place - 1] = voiture;
            DetacherMemoirePartagee(semId, mem);
            voituriers.erase(pid);

            AfficherPlace(place, voiture.usager, voiture.numero, voiture.arrivee);
        }
    }
} //----- fin de GererFinVoiturier

static int InitialiserBarriereEntree ( enum TypeBarriere barriere )
// Mode d'emploi :
//    <barriere> : l'identifiant de la barrière d'entrée à gèrer
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
    // Récupérer le sémaphore associé et la mémoire partagée
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
void BarriereEntree ( enum TypeBarriere barriere )
// Algorithme :
//    Cette fonction tourne à l'infini, attendant la réception de messages
//    dans la file de messages de cette barrière. Lorsqu'un message
//    arrive, il est interprété comme signifiant l'arrivée d'une voiture à
//    la barrière ; la fonction se met éventuellement en attente s'il n'y
//    a plus de place, puis un voiturier est lancé pour garer la voiture.
//    La fonction attend alors la prochaine voiture.
//
{
    // Initialiser la barrière
    int fileId = InitialiserBarriereEntree(barriere);

    for (;;)
    {
        // Essayer de récuperer un message. Comme la récupération peut être
        // interrompue par un signal, on laisse de côté tout appel renvoyant
        // un code d'erreur et on réessaie.
        msg_voiture_t msg;
        while (msgrcv(fileId, &msg, MSG_TAILLE, MSG_ENTREE, 0) < 0);

        // Affichage de la voiture en attente à la barrière
        voiture_t voiture = {msg.usager, msg.numero, time(NULL)};
        DessinerVoitureBarriere(barriere, voiture.usager);

        // Vérification qu'il n'y pas de voitures en attente. S'il y a des
        // voitures en attente, alors il faut également mettre cette voiture
        // en attente. En effet, il n'est pas suffisant de regarder le
        // nombre de places occupées, puisque nous pourrions avoir la
        // situation suivante :
        // - le parking est plein et il y a une ou deux voitures en attente
        //   dans des barrières différentes,
        // - au moment où une voiture sort, une voiture entre à une barrière
        //   où il n'y a aucune voiture en attente,
        // - la nouvelle voiture réserve la mémoire partagée avant les
        //   voitures en attente ailleurs, et voit qu'il y a une place libre,
        //   donc elle lance un voiturier,
        // - le comportement est ensuite indéfini quand la voiture en attente
        //   essaie également de lancer le voiturier.
        // Cette vérification permet donc de s'assurer que ce problème n'aura
        // pas lieu.
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

        // Si toutes les places sont occupées ou il y a au moins une voiture
        // en attente, déposer une requête et attendre qu'elle soit réalisée
        if (mem->placesOccupees == NB_PLACES || voituresEnAttente)
        {
            requete_t requete;
            requete.usager = voiture.usager;
            requete.arrivee = voiture.arrivee;
            mem->requetes[barriere - 1] = requete;
            DetacherMemoirePartagee(semId, mem);
            AfficherRequete(barriere, requete.usager, time(NULL));

            sembuf reserver = SEM_BARRIERE_RESERVER;
            reserver.sem_num = barriere;
            while (semop(semId, &reserver, 1) < 0);
            mem = AttacherMemoirePartagee(semId, shmId);
        }

        // Incrémenter le nombre de places occupées, puis lancer le voiturier
        // pour garer la voiture arrivée
        mem->placesOccupees++;
        DetacherMemoirePartagee(semId, mem);
        pid_t voiturier = GarerVoiture(barriere);
        voiture.arrivee = time(NULL);
        voituriers[voiturier] = voiture;

        // Attendre un certain temps avant de traiter la prochaine voiture
        sleep(TEMPO);
    }
} //----- fin de BarriereEntree

