/*************************************************************************
         BarriereEntree  -  Gère une barrière d'entrée du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//------ Interface de la tâche <BarriereEntree> (fichier BarriereEntree.h)
#if ! defined ( BARRIERE_E_H )
#define BARRIERE_E_H

//------------------------------------------------------------------------
// Rôle de la tâche <BarriereEntree>
//
// Barriere Entrée
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>

#include <Outils.h>
#include "config.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

void BarriereEntree(enum TypeBarriere barriere);
// Mode d'emploi :
// Point d'entrée d'une barrière d'entrèe
// Contrat :
//

int InitialiserBarriereEntree ( enum TypeBarriere barriere );
// Mode d'emploi :
// Initialise une barrière d'entrèe suivant le type donné en paramètre
// Contrat :
//

#endif // BARRIERE_ENTREE_H
