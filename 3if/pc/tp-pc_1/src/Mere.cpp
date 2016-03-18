#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <Outils.h>
#include <Heure.h>

#include "Simulateur.h"
#include "BarriereEBPP.h"

int main ()
{
    pid_t pidHeure, pidSimulateur, pidBarriereEBPP;
    
    //enum TypeTerminal terminal = XTERM;
    enum TypeTerminal terminal = VT220;

    /* --- Initialisation --- */
    InitialiserApplication(terminal);
    pidHeure = ActiverHeure();

    key_t cleBarriereEBPP = ftok("/bin/tp-pc_1", 's');
    int identifiantBarriereEBPP = msgget(cleBarriereEBPP, IPC_CREAT);
    
    if((pidSimulateur=fork()) == 0)
    {
        // Fils - Simulateur
        Simulateur();
    }
    else
    {
        // Pere
        if((pidBarriereEBPP=fork()) == 0)
        {
            // Fils - BarriereEBPP            
            BarriereEBPP();
        }
        else
        {
            // Pere
            /* --- Moteur --- */
            waitpid(pidSimulateur, NULL, 0);

            /* --- Destruction --- */
            msgctl(identifiantBarriereEBPP, IPC_RMID, NULL);
            kill(pidHeure, SIGUSR2);
            TerminerApplication(true);
            exit(0);
        }
    }

    return 0;
}
