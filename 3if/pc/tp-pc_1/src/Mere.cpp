#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include <Heure.h>
#include <Outils.h>

#include "config.h"
#include "BarriereEntree.h"
#include "BarriereSortie.h"
#include "Simulateur.h"

int main ()
{
    //enum TypeTerminal terminal = XTERM;
    enum TypeTerminal terminal = VT220;

    size_t MAX_TACHES = NB_BARRIERES + 2;
    pid_t tachesPid[MAX_TACHES];
    size_t taches = 0;

    /* --- Initialisation --- */
    InitialiserApplication(terminal);
    int boites[] = {
        msgget(CLE_BARRIERE_PBP, IPC_CREAT | 0600),
        msgget(CLE_BARRIERE_ABP, IPC_CREAT | 0600),
        msgget(CLE_BARRIERE_EGB, IPC_CREAT | 0600),
        msgget(CLE_BARRIERE_SGB, IPC_CREAT | 0600)
    };
    int shmid = shmget(CLE_PARKING, 8 * sizeof(voiture_t), IPC_CREAT | 0600);
    tachesPid[taches++] = ActiverHeure();

    if ((tachesPid[taches++] = fork()) == 0)
    {
        // Fils - Barrière S (Sortie)
        BarriereSortie(shmid);
    }
    else
    {
        // Père
        if ((tachesPid[taches++] = fork()) == 0)
        {
            // Fils - Barrière PBP (Blaise Pascal - Profs)
            BarriereEntree(PROF_BLAISE_PASCAL, shmid);
        }
        else
        {
            // Père
            if ((tachesPid[taches++] = fork()) == 0)
            {
                // Fils - Simulateur
                Simulateur();
            }
            else
            {
                // Père
                /* --- Moteur --- */
                waitpid(tachesPid[--taches], NULL, 0);

                /* --- Destruction --- */
                while (taches)
                {
                    kill(tachesPid[--taches], SIGUSR2);
                }
                shmctl(shmid, IPC_RMID, NULL);
                for (size_t i = 0; i < NB_BARRIERES; i++)
                {
                    msgctl(boites[i], IPC_RMID, NULL);
                }
                shmctl(shmid, IPC_RMID, 0);
                TerminerApplication(true);
                exit(0);
            }
        }
    }

    return 0;
}
