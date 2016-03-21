/*************************************************************************
                           Simulateur  -  description
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Marc Gagné & Arnaud Favier
    e-mail               : marc.gagne@insa-lyon.fr, arnaud.favier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la module <Simulateur> (fichier Simulateur.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <sys/msg.h>

#include "config.h"
#include "Simulateur.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int boitePBP;
static int boiteABP;
static int boiteEGB;
static int boiteSGB;
static unsigned int nbVoiture;

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

static void InitialiserSimulateur ( void )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    boitePBP = msgget(CLE_BARRIERE_PBP, 0666);
    boiteABP = msgget(CLE_BARRIERE_ABP, 0666);
    boiteEGB = msgget(CLE_BARRIERE_EGB, 0666);
    boiteSGB = msgget(CLE_BARRIERE_SGB, 0666);
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
        int boite, long mtype, unsigned int numero, unsigned int place
)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    msg_voiture msg = { mtype, numero, place};
    msgsnd(boite, &msg, sizeof(msg.place), 0);
} //----- fin de EnvoyerMessage

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom

void Simulateur (void)
// Algorithme :
//
{
    InitialiserSimulateur();
    for(;;)
    {
        Menu();
    }
} //----- fin de Simulateur


void Commande (char code, unsigned int valeur)
// Algorithme :
//
{
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
            case PROF_BLAISE_PASCAL:
                EnvoyerMessage(boitePBP, MSG_ENTREE_PROF, nbVoiture, 0);
                break;
            case ENTREE_GASTON_BERGER:
                EnvoyerMessage(boiteEGB, MSG_ENTREE_PROF, nbVoiture, 0);
                break;
            default:
                Afficher(MESSAGE, "Erreur : barrière non reconnue");
            }
            nbVoiture = (nbVoiture + 1) % 1000;
            break;
        case 'a':
        case 'A':
            switch (valeur)
            {
            case AUTRE_BLAISE_PASCAL:
                EnvoyerMessage(boiteABP, MSG_ENTREE_AUTRE, nbVoiture, 0);
                break;
            case ENTREE_GASTON_BERGER:
                EnvoyerMessage(boiteEGB, MSG_ENTREE_AUTRE, nbVoiture, 0);
                break;
            default:
                Afficher(MESSAGE, "Erreur : barrière non reconnue");
            }
            nbVoiture = (nbVoiture + 1) % 1000;
            break;
        case 's':
        case 'S':
            EnvoyerMessage(boiteSGB, MSG_SORTIE, nbVoiture, valeur);
            break;
        default:
            Afficher(MESSAGE, "Erreur : commande non reconnue");
            break;
    }
} //----- fin de Commande

