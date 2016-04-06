/*************************************************************************
         BarriereEntree  -  Gère une barrière d'entrée du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//------ Interface de la tâche <BarriereEntree> (fichier BarriereEntree.h)
#if ! defined ( BARRIERE_ENTREE_H )
#define BARRIERE_ENTREE_H

//------------------------------------------------------------------------
// Rôle de la tâche <BarriereEntree>
//
// La tâche <BarriereEntree> gère toutes les entrées de voiture au
// niveau d'une des barrières d'entrée, identifiée par son code
// <TypeBarriere>. Elle lance notamment les voituriers pour garer les
// voitures et les fait attendre lorsque le parking est plein.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <Outils.h>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void BarriereEntree ( enum TypeBarriere barriere );
// Mode d'emploi :
//    <barriere> : l'identifiant de la barrière d'entrée à gèrer
//    Lance la tâche <BarriereEntree>, qui tournera jusqu'à réception d'un
//    signal <SIGUSR2>, pour la barrière d'entrée <barriere>.
//
// Contrat :
//    - la barrière ne doit pas déjà être gérée par un autre processus
//    - les mécanismes IPC pour cette barrière doivent déjà avoir été créés
//    - le comportement est indéterminé en cas de non-respect des contraintes
//

#endif // BARRIERE_ENTREE_H
