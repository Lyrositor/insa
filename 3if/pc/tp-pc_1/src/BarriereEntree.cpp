/*************************************************************************
           BarriereEntree  -  Gère une barrière d'entrée du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <BarriereEntree> (fichier BarriereEntree.cpp) -

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "BarriereEntree.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

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

static void DetruireBarriereEntree ( void )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    exit(0);
} //----- fin de DetruireBarriereEntree

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom

int InitialiserBarriereEntree ( enum TypeBarriere barriere )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    switch(barriere)
    {
        case PROF_BLAISE_PASCAL:
            return msgget(CLE_BARRIERE_PBP, 0600);
            break;
        case AUTRE_BLAISE_PASCAL:
            return msgget(CLE_BARRIERE_ABP, 0600);
            break;
        case ENTREE_GASTON_BERGER:
            return msgget(CLE_BARRIERE_EGB, 0600);
            break;
        default:
            return 0;
            break;
    }
} //----- fin de InitialiserBarriereEntree

void BarriereEntree ( enum TypeBarriere barriere )
// Algorithme :
//
{
    int boite;
    boite = InitialiserBarriereEntree(barriere);
    for(;;)
    {
        msg_voiture msg;
        msgrcv(boite, &msg, sizeof(msg_voiture) - sizeof(msg.mtype), 0, 0);

        TypeUsager typeUsage = AUCUN;
        switch(msg.mtype)
        {
            case MSG_ENTREE_PROF:
                typeUsage = PROF;
                break;
            case MSG_ENTREE_AUTRE:
                typeUsage = AUTRE;
                break;
            default:
                break;
        }

        DessinerVoitureBarriere(barriere, typeUsage);
    }

    DetruireBarriereEntree();
} //----- fin de BarriereEntree
