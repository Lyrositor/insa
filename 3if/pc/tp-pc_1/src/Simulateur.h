/*************************************************************************
                           Simulateur  -  description
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Marc Gagné & Arnaud Favier
    e-mail               : marc.gagne@insa-lyon.fr, arnaud.favier@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Simulateur> (fichier Simulateur.h) -------
#if ! defined ( SIMULATEUR_H )
#define SIMULATEUR_H

//------------------------------------------------------------------------
// Rôle du module <Simulateur>
//
// Recevoir les entrées claviers et les interpréter
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <stdlib.h>
#include <unistd.h>

#include <Outils.h>
#include <Menu.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
void Simulateur (void);
// Mode d'emploi :
// Point d'entrée du Simulateur qui appele le menu
// Contrat :
//


void Commande (char code, unsigned int valeur);
// Mode d'emploi :
// Voir documentation annexe Menu()
// Contrat :
// aucun

#endif // SIMULATEUR_H
