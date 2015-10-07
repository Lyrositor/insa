/*************************************************************************
                           Collection  -   Collection dynamique d'entiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

//---------- Réalisation de la classe Collection (fichier Collection) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "collection.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Collection::Afficher ()
// Algorithme :
{
    for (int i=0; i<elements; i++)
        cout << collection[i] << ' ';
    cout << endl;
} //----- Fin de Méthode

void Collection::Ajouter (int jeton)
// Algorithme :
{
    if (elements >= alloue)
        Ajuster(elements+1);
    collection[elements] = jeton;
    elements++;

} //----- Fin de Méthode

void Collection::Retirer (int n, int items[])
// Algorithme :
{
    bool delete;
    int* tmp = collection;
    collection = new int[n];
    int k = 0;
    for (int i = 0; i < elements; i++) {
        delete = false;
        for (int j = 0; j < n; j++) {
            if (items[j] == elements[i]) {
                delete = true;
                break;
            }
        }
        if (!delete) {
            collection[k] = elements[i];
            k++;
        }
    }
    elements = k;
    Ajuster(elements);
    delete tmp;
} //----- Fin de Méthode

void Collection::Ajuster (int n)
// Algorithme :
{
    alloue = n;
    int* tmp = collection;
    collection = new int[n];
    for (int i=0; i < elements && i < alloue; i++)
        collection[i] = tmp[i];
    delete tmp;
} //----- Fin de Méthode

void Collection::Reunir (Collection* collection)
// Algorithme :
{
} //----- Fin de Méthode

//-------------------------------------------- Constructeurs - destructeur
Collection::Collection (int n)
// Algorithme :

{
#ifdef MAP
    cout << "Appel au constructeur de Collection" << endl;
#endif
    Init(n);
} //----- Fin de Collection

Collection::Collection (int n, int items[])
// Algorithme :

{
#ifdef MAP
    cout << "Appel au constructeur de Collection" << endl;
#endif
    Init(n);
    for (int i=0; i<n; i++)
        Ajouter(items[i]);
} //----- Fin de Collection


Collection::~Collection ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de Collection" << endl;
#endif
    delete collection;
} //----- Fin de ~Collection


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Collection::Init (int n)
// Algorithme :
{
    alloue = n;
    elements = 0;
    collection = new int[n];
} //----- Fin de Méthode
