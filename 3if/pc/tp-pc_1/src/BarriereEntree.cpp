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

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom

void BarriereEntree(enum TypeBarriere barriere)
// Algorithme :
//
{
    int boite = InitialiserBarriereEntree(barriere);
    
    for(;;)
    {
        msg_voiture msg;
        msgrcv(boite, &msg, sizeof(msg) - sizeof(msg.mtype), MSG_ENTREE_PROF, 0);
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

