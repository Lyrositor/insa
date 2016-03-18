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
#include "Simulateur.h"

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

void Simulateur (void)
// Algorithme :
//
{
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
            exit(0);
            break;
        case 'p':
        case 'P':
            break;
        case 'a':
        case 'A':
            break;
        case 's':
        case 'S':
            break;
        default:
            Afficher(MENU, "Erreur : commande non reconnue");
            break;
    }
} //----- fin de Commande

