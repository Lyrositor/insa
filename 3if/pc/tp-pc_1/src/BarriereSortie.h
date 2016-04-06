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
// La tâche <BarriereSortie> gère toutes les voitures qui essaient de
// sortir du parking. Puisqu'il n'y a qu'une sortie, il ne devrait y avoir
// qu'une seule instance de cette tâche ; le comportement est indéfini
// sinon. Chaque fois qu'une voiture cherche à sortir, un voiturier est
// lancé pour la garer.
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
//    <barriere> : l'identifiant de la barrière de sortie à gèrer
//    Lance la tâche <BarriereSortie>, qui tournera jusqu'à réception d'un
//    signal <SIGUSR2>, pour la barrière de sortie <barriere>.
//
// Contrat :
//    - la barrière ne doit pas déjà être gérée par un autre processus
//    - aucune autre barrière de sortie ne doit exister
//    - les mécanismes IPC pour cette barrière doivent déjà avoir été créés
//    - le comportement est indéterminé en cas de non-respect des contraintes
//

#endif // BARRIERE_SORTIE_H
