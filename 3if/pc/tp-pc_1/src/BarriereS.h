/*************************************************************************
           BarriereS  -  Gère la barrière de sortie du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <BarriereS> (fichier BarriereS.h) -----
#if ! defined ( BARRIERE_S_H )
#define BARRIERE_S_H

//------------------------------------------------------------------------
// Rôle de la tâche <BarriereS>
//
// Gère la barrière de sortie du parking.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <stdlib.h>
#include <unistd.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

void BarriereS (void);
// Mode d'emploi :
// Point d'entrée de la tâche pour la barrière de sortie.
// Contrat :
//

#endif // BARRIERE_S_H
