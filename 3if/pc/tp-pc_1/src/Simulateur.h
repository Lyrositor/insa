/*************************************************************************
         Simulateur  -  Simule l'arrivée et la sortie de voitures
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Simulateur> (fichier Simulateur.h) ---
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
void Simulateur ( void );
// Mode d'emploi :
//     Lance l'exécution de la tâche <Simulateur>, qui tournera jusqu'à ce
//     que l'utiliasteur appuie sur 'E'.
//
// Contrat :
//     L'interface graphique doit déjà avoir été initialisée.
//

void Commande ( char code, unsigned int valeur );
// Mode d'emploi :
//    <code> : le code de la commande ('e|E', 'p|P', 'a|A' ou 's|S')
//    <valeur> : la valeur secondaire pour certaines commandes
//    Exécute les instructions nécessaires pour la commande lancée.
//    Voir la documentation de <Menu> pour plus d'informations.
//
// Contrat :
//     Devrait être appelé par <Menu> seulement.
//

#endif // SIMULATEUR_H
