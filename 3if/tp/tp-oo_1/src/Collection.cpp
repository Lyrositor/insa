/*************************************************************************
               Collection  - Collection dynamique d'entiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

//---------- Réalisation de la classe <Collection> (fichier Collection.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Collection.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

void Collection::Afficher ()
// Algorithme :
{
    for (unsigned int i = 0; i < elements; i++)
    {
        cout << tableau[i] << ' ';
    }
    cout << endl;
} //----- Fin de Méthode

void Collection::Ajouter (int valeur)
// Algorithme :
{
    if (elements >= alloue)
    {
        Ajuster(elements + 1);
    }
    tableau[elements] = valeur;
    elements++;

} //----- Fin de Méthode

void Collection::Retirer (unsigned int n, int retirer[])
// Algorithme :
{
    if (n == 0)
    {
        return;
    }

    int* tmp = tableau;
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
} //----- Fin de Méthode

void Collection::Ajuster (unsigned int n)
// Algorithme :
{
    alloue = n;
    elements = (elements > alloue) ? alloue: elements;
    int* tmp = tableau;
    tableau = new int[n];
    for (unsigned int i = 0; i < elements && i < alloue; i++)
    {
        tableau[i] = tmp[i];
    }
    delete[] tmp;
} //----- Fin de Méthode

void Collection::Reunir (Collection* collection)
// Algorithme :
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
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Collection::Collection (unsigned int n)
// Algorithme :
{
#ifdef MAP
    cout << "Appel au constructeur de Collection" << endl;
#endif
    Init(n);
} //----- Fin de Collection

Collection::Collection (unsigned int n, int items[])
// Algorithme :
{
#ifdef MAP
    cout << "Appel au constructeur de Collection" << endl;
#endif
    Init(n);
    for (unsigned int i = 0; i < n; i++)
    {
        Ajouter(items[i]);
    }
} //----- Fin de Collection

Collection::~Collection ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de Collection" << endl;
#endif
    delete[] tableau;
} //----- Fin de ~Collection


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Collection::Init (unsigned int n)
// Algorithme :
{
    alloue = n;
    elements = 0;
    tableau = new int[n];
} //----- Fin de Méthode

//------------------------------------------------------- Méthodes privées
