#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <Outils.h>
#include <Heure.h>

int main (int argc, char* argv[])
{
    //enum TypeTerminal terminal = XTERM;
    enum TypeTerminal terminal = VT220;

    /* --- Initialisation --- */
    InitialiserApplication(terminal);
    pid_t pidHeure = ActiverHeure();

    /* --- Moteur --- */
    sleep(3);
    
    /* --- Destrcution --- */
    kill(pidHeure, SIGUSR2);
    TerminerApplication(true);

    return 0;
}
