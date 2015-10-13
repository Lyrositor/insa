/*************************************************************************
            CollectionEntiers  - Collection dynamique d'entiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

// Réalisation de la classe <CollectionEntiers> (fichier CollectionEntiers.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "CollectionEntiers.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

void CollectionEntiers::Afficher ()
// Algorithme : Parcourt tous les éléments de 'tableau' et affiche chaque
// valeur, séparées par un espace (note : il y aura un espace à la suite
// du dernier élément, si 'tableau' est non-vide).
{
    for (unsigned int i = 0; i < elements; i++)
    {
        cout << tableau[i] << ' ';
    }
    cout << endl;
} //----- Fin de Afficher

void CollectionEntiers::Ajouter (int valeur)
// Algorithme : Ajuste la mémoire allouée si une quantité insuffisante a
// été allouée, puis ajoute 'valeur' au tableau de valeurs 'tableau'.
{
    if (elements >= alloue)
    {
        Ajuster(elements + 1);
    }
    tableau[elements] = valeur;
    elements++;

} //----- Fin de Ajouter

void CollectionEntiers::Retirer (unsigned int n, int retirer[])
// Algorithme : Si la liste est non-vide :
// 1.  Le pointeur du tableau des anciennes valeurs est copié dans un
//     pointeur temporaire 'tmp' et 'tableau' est réinitialisé avec la
//     même taille.
// 2.  Une boucle itère sur chaque ancienne valeur (à partir de 'tmp') :
//     i.  Si la valeur n'est pas dans le tableau de valeurs à retirer,
//         elle est copiée dans le nouveau 'tableau'.
//     ii. Sinon, la valeur n'est pas recopiée (ce qui revient à la
//         supprimer).
// 3.  Le nouveau 'tableau' est ré-ajusté pour avoir une taille mémoire au
// plus juste.
// 4. L'ancien 'tableau' (pointé par 'tmp') est supprimé.
{
    if (n == 0)
    {
        return;
    }

    int * tmp = tableau;
    tableau = new int[elements];
    unsigned int k = 0;
    for (unsigned int i = 0; i < elements; i++)
    {
        bool conserver = true;
        for (unsigned int j = 0; j < n; j++)
        {
            if (retirer[j] == tmp[i])
            {
                conserver = false;
                break;
            }
        }
        if (conserver)
        {
            tableau[k] = tmp[i];
            k++;
        }
    }
    elements = k;
    Ajuster(elements);
    delete[] tmp;
} //----- Fin de Retirer

void CollectionEntiers::Ajuster (unsigned int n)
// Algorithme : Le pointeur du tableau est copié dans un pointeur
// temporaire 'tmp' et 'tableau' est ré-initialisé pour devenir un
// tableau d'entiers de taille 'n'. Chaque élément de l'ancien tableau
// y est recopié, puis l'ancien tableau est supprimé. Si le nouveau
// tableau est plus petit, on garde tous les éléments, dans l'ordre dans
// lequel ils sont stockés, qui peuvent rentrer dans le nouveau tableau.
{
    alloue = n;
    elements = (elements > alloue) ? alloue: elements;
    int * tmp = tableau;
    tableau = new int[n];
    for (unsigned int i = 0; i < elements && i < alloue; i++)
    {
        tableau[i] = tmp[i];
    }
    delete[] tmp;
} //----- Fin de Ajuster

void CollectionEntiers::Reunir (CollectionEntiers * collection)
// Algorithme : S'il n'y a pas assez de mémoire allouée pour contenir les
// éléments de cette collection ainsi que ceux de 'collection', la taille
// de cette collection est augmentée ; sinon elle demeure inchangée.
// Ensuite, chaque élément de 'collection' est copié dans cette
// collection, et le nombre d'éléments de cette collection est ajusté.
{
    if (collection->elements + elements > alloue)
    {
        Ajuster(collection->elements + elements);
    }
    for (unsigned int i = 0; i < collection->elements; i++)
    {
        tableau[elements + i] = collection->tableau[i];
    }
    elements += collection->elements;
} //----- Fin de Reunir


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
CollectionEntiers::CollectionEntiers(unsigned int n)
// Algorithme : Initialise les attributs grâce à Init, sans opérations
// supplémentaires.
{
#ifdef MAP
    cout << "Appel au constructeur de CollectionEntiers" << endl;
#endif
    Init(n);
} //----- Fin de CollectionEntiers

CollectionEntiers::CollectionEntiers(unsigned int n, int valeurs[])
// Algorithme : Initialise les attributs grâce à Init, puis ajoute toutes
// les 'valeurs' au tableau.
{
#ifdef MAP
    cout << "Appel au constructeur de CollectionEntiers" << endl;
#endif
    Init(n);
    for (unsigned int i = 0; i < n; i++)
    {
        Ajouter(valeurs[i]);
    }
} //----- Fin de CollectionEntiers

CollectionEntiers::~CollectionEntiers( )
// Algorithme : Libère la mémoire allouée au tableau de valeurs lors de
// l'initialisation.
{
#ifdef MAP
    cout << "Appel au destructeur de CollectionEntiers" << endl;
#endif
    delete[] tableau;
} //----- Fin de CollectionEntiers


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void CollectionEntiers::Init (unsigned int n)
// Algorithme : Initialise les attributs avec leurs valeurs initiales ;
// une collection de taille 'n', contenant 0 éléments, est créée.
{
    alloue = n;
    elements = 0;
    tableau = new int[n];
} //----- Fin de Init

//------------------------------------------------------- Méthodes privées
