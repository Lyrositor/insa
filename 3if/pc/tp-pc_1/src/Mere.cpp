#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include <Heure.h>
#include <Outils.h>

#include "Config.h"
#include "BarriereEntree.h"
#include "BarriereSortie.h"
#include "Simulateur.h"

int main ()
{
    /* --- Initialisation --- */

    // Initialisation de l'application
    //enum TypeTerminal terminal = XTERM;
    enum TypeTerminal terminal = VT220;
    InitialiserApplication(terminal);
    size_t MAX_TACHES = NB_BARRIERES + 2;
    pid_t tachesPid[MAX_TACHES];
    size_t taches = 0;

    // Initialiser les files de message
    int filesId[NB_BARRIERES];
    for (size_t i = 0; i < NB_BARRIERES; i++)
    {
        filesId[i] = msgget(CLE_BARRIERES[i], IPC_CREAT | 0600);
    }

    // Initialiser le sémaphore du mutex à 1 (car il n'est pas en cours
    // d'utilisation) et les sémaphores des barrières à 0 (car il n'y a aucune
    // requête en cours).
    int semId = semget(CLE_SEMAPHORE, NUM_SEMAPHORES, IPC_CREAT | 0600);
    semctl(semId, SEM_MUTEX, SETVAL, 1);
    semctl(semId, SEM_PBP, SETVAL, 0);
    semctl(semId, SEM_ABP, SETVAL, 0);
    semctl(semId, SEM_EGB, SETVAL, 0);

    // Initialiser la mémoire partagée avec aucune place occupée et aucune
    // requête envoyée
    int shmId = shmget(CLE_MEMOIRE_PARTAGEE, sizeof(memoire_partagee_t), IPC_CREAT | 0600);
    memoire_partagee_t * mem = (memoire_partagee_t *) shmat(shmId, NULL, 0);
    for (size_t i = 0; i < NB_PLACES; i++)
    {
        mem->places[i] = PLACE_VIDE;
    }
    for (size_t i = 0; i < NB_BARRIERES_ENTREE; i++)
    {
        mem->requetes[i] = REQUETE_VIDE;
    }
    shmdt(mem);

    // Lancer toutes les tâches
    tachesPid[taches++] = ActiverHeure();
    if ((tachesPid[taches++] = fork()) == 0)
    {
        // Fils - Barrière S (Sortie)
        BarriereSortie(SORTIE_GASTON_BERGER);
    }
    else
    {
        // Père
        if ((tachesPid[taches++] = fork()) == 0)
        {
            // Fils - Barrière Entrée (Blaise Pascal - Profs)
            BarriereEntree(PROF_BLAISE_PASCAL);
        }
        else
        {
            // Père
            if ((tachesPid[taches++] = fork()) == 0)
            {
                // Fils - Barrière Entrée (Blaise Pascal - Autres)
                BarriereEntree(AUTRE_BLAISE_PASCAL);
            }
            else
            {
                // Père
                if ((tachesPid[taches++] = fork()) == 0)
                {
                    // Fils - Barrière Entrée (Gaston Berger)
                    BarriereEntree(ENTREE_GASTON_BERGER);
                }
                else
                {
                    // Père
                    if ((tachesPid[taches++] = fork()) == 0) {
                        // Fils - Simulateur
                        Simulateur();
                    }
                    else {
                        // Père
                        /* --- Moteur --- */
                        waitpid(tachesPid[--taches], NULL, 0);

                        /* --- Destruction --- */
                        while (taches)
                        {
                            kill(tachesPid[--taches], SIGUSR2);
                        }
                        semctl(semId, 0, IPC_RMID, NULL);
                        shmctl(shmId, IPC_RMID, NULL);
                        for (size_t i = 0; i < NB_BARRIERES; i++)
                        {
                            msgctl(filesId[i], IPC_RMID, NULL);
                        }
                        TerminerApplication(true);
                        exit(0);
                    }
                }
            }
        }
    }

    return 0;
}
