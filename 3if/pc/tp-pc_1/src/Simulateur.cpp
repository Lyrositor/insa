/*************************************************************************
         Simulateur  -  Simule l'arrivée et la sortie de voitures
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Simulateur> (fichier Simulateur.cpp)

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/msg.h>

//------------------------------------------------------ Include personnel
#include "Config.h"
#include "Simulateur.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
// Tableau de toutes les files de message des barrières
int filesId[NB_BARRIERES];

// Nombre de voitures qui sont passés par la barrière
// Note : s'il y a un overflow de <nbVoiture>, le prochain numéro
// minéralogique calculé ne sera pas le prochain séquentiellement.
static unsigned int nbVoiture;

//------------------------------------------------------ Fonctions privées
static void InitialiserSimulateur ( void )
// Mode d'emploi :
//    Prépare le simulateur pour envoyer des messages.
//
// Contrat :
//    (Aucun)
//
// Algorithme :
//    Récupère toutes les files de message qui ont été créées, puis met le
//    compteur de voitures à 0.
//
{
    for (size_t i = 0; i < NB_BARRIERES; i++)
    {
        filesId[i] = msgget(CLE_BARRIERES[i], IPC_CREAT | DROITS);
    }
    nbVoiture = 0;
} //----- fin de InitialiserSimulateur

static void DetruireSimulateur ( void )
// Mode d'emploi :
//    Lance la destruction du simulateur.
//
// Contrat :
//    (Aucun)
//
// Algorithme :
//    La tâche doit seulement renvoyer pour que la tâche <Mere> initie la
//    destruction de l'application.
//
{
    exit(0);
} //----- fin de DetruireSimulateur

static void EnvoyerMessage (
        int fileId, enum MsgBarriere mtype, TypeUsager usager,
        unsigned int numero, unsigned int place
)
// Mode d'emploi :
//    <file> : ID de la file de messages à utiliser
//    <mtype> : le type de message à envoyer
//    <usager> : le type d'usager dans le message
//    <numero> : le numéro de voiture dans le message
//    <place> : la place de la voiture dans le message
//    Envoie un message de type <msg_voiture_t> à la file de messages
//    <fileId>.
//
// Contrat :
//    La file de messages doit avoir été créée précédemment.
//
// Algorithme :
//    Crée la structure du message, puis l'envoie à la file de messages.
//
{
    msg_voiture_t msg = {mtype, usager, numero, place};
    msgsnd(fileId, &msg, MSG_TAILLE, 0);
} //----- fin de EnvoyerMessage

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Simulateur ( void )
// Algorithme :
//    Initialise le simulateur, puis attend des commandes menu de
//    l'utilisateur à l'infini.
//
{
    InitialiserSimulateur();
    for (;;)
    {
        Menu();
    }
} //----- fin de Simulateur


void Commande ( char code, unsigned int valeur )
// Algorithme :
//    Exécute les instructions nécessaire pour la commande qui vient
//    d'être envoyée en envoyant des messages aux barrières pour 'P', 'A'
//    et 'S' et en terminant la tâche pour 'E'.
{
    Effacer(MESSAGE);
    int fileId;
    switch(code)
    {
    case 'e':
    case 'E':
        DetruireSimulateur();
        break;

    case 'p':
    case 'P':
        switch (valeur)
        {
            case 1:
                fileId = PROF_BLAISE_PASCAL - 1;
                break;
            case 2:
                fileId = ENTREE_GASTON_BERGER - 1;
                break;
            default:
                return;
        }
        EnvoyerMessage(filesId[fileId], MSG_ENTREE, PROF, 1 + nbVoiture++ % MAX_NUM_VOITURE, 0);
        break;

    case 'a':
    case 'A':
        switch (valeur)
        {
            case 1:
                fileId = AUTRE_BLAISE_PASCAL - 1;
                break;
            case 2:
                fileId = ENTREE_GASTON_BERGER - 1;
                break;
            default:
                return;
        }
        EnvoyerMessage(filesId[fileId], MSG_ENTREE, AUTRE, 1 + nbVoiture++ % MAX_NUM_VOITURE, 0);
        break;

    case 's':
    case 'S':
        EnvoyerMessage(filesId[SORTIE_GASTON_BERGER - 1], MSG_SORTIE, AUCUN, 0, valeur);
        break;

    default:
        break;
	}
} //----- fin de Commande

