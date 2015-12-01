/*************************************************************************
       ArgumentParser  - Traiteur d'arguments de ligne de commande
                             -------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

// Réalisation de la classe <ArgumentParser> (fichier ArgumentParser.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "ArgumentParser.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
void ArgumentParser::addArgument()
// Algorithme :
{
#ifdef MAP
    cout << "Appel à addArgument de ArgumentParser" << endl;
#endif
} //----- Fin de addArgument

void ArgumentParser::addOption()
// Algorithme :
{
#ifdef MAP
    cout << "Appel à addOption de ArgumentParser" << endl;
#endif
} //----- Fin de addOption

ArgumentParser::ArgumentParser()
// Algorithme :
{
#ifdef MAP
    cout << "Appel au constructeur de ArgumentParser" << endl;
#endif
} //----- Fin de ArgumentParser

ArgumentParser::~ArgumentParser()
// Algorithme :
{
#ifdef MAP
    cout << "Appel au destructeur de ArgumentParser" << endl;
#endif
} //----- Fin de ~ArgumentParser

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
