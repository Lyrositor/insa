/*************************************************************************
                           Simulateur  -  description
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Marc Gagné & Arnaud Favier
    e-mail               : marc.gagne@insa-lyon.fr
                           arnaud.favier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la module <Simulateur> (fichier Simulateur.cpp) ---

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
int filesId[NB_BARRIERES];
static unsigned int nbVoiture;

//------------------------------------------------------ Fonctions privées

static void InitialiserSimulateur ( void )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
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
//
// Contrat :
//
// Algorithme :
//
{
    exit(0);
} //----- fin de DetruireSimulateur

static void EnvoyerMessage (
        int boite, enum MsgBarriere mtype, TypeUsager usager, unsigned int numero,
        unsigned int place
)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    msg_voiture_t msg = {mtype, usager, numero, place};
    msgsnd(boite, &msg, MSG_TAILLE, 0);
} //----- fin de EnvoyerMessage

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Simulateur ( void )
// Algorithme :
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
//
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

