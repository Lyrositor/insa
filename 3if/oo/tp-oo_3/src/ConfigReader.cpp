/*******************************************************************************
               ConfigReader - Lecteur de fichier de configuration
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <ConfigReader> (fichier ConfigReader.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système

//------------------------------------------------------------ Include personnel
#include "ConfigReader.h"
#include "Logger.h"

//------------------------------------------------------------------- Constantes

//---------------------------------------------------------- Variables de classe

//----------------------------------------------------------------- Types privés


//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies

//----------------------------------------------------------- Méthodes publiques

//------------------------------------------------------- Surcharge d'opérateurs
ConfigReader & ConfigReader::operator= (const ConfigReader & reader)
// Algorithme :
{
    Logger::Debug("Appel à ConfigReader::operator=");
    return *this;
} //----- Fin de la surcharge d'opérateur =

//-------------------------------------------------- Constructeurs - destructeur
ConfigReader::ConfigReader ()
// Algorithme :
{
    Logger::Debug("Appel au constructeur de ConfigReader");
} //----- Fin du constructeur

ConfigReader::ConfigReader (const ConfigReader & reader)
// Algorithme :
{
    Logger::Debug("Appel au constructeur de copie de ConfigReader");
} //----- Fin du constructeur de copie

ConfigReader::~ConfigReader ()
// Algorithme :
{
    Logger::Debug("Appel au destructeur de ConfigReader");
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées

//------------------------------------------------------------- Méthodes privées
