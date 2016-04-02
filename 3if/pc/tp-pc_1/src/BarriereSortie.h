/*************************************************************************
           BarriereSortie  -  Gère la barrière de sortie du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//------ Interface de la tâche <BarriereSortie> (fichier BarriereSortie.h)
#if ! defined ( BARRIERE_SORTIE_H )
#define BARRIERE_SORTIE_H

//------------------------------------------------------------------------
// Rôle de la tâche <BarriereSortie>
//
// Gère la barrière de sortie du parking.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <Outils.h>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void BarriereSortie ( enum TypeBarriere barriere );
// Mode d'emploi :
// Point d'entrée de la tâche pour la barrière de sortie.
// Contrat :
//

#endif // BARRIERE_S_H
