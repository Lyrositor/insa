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

//------------------------------------------------------------------- Constantes

//---------------------------------------------------------- Variables de classe

//----------------------------------------------------------------- Types privés


//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies

//----------------------------------------------------------- Méthodes publiques

//------------------------------------------------------- Surcharge d'opérateurs
ConfigReader & ConfigReader::operator= (const ConfigReader & reader)
{
    return *this;
}

//-------------------------------------------------- Constructeurs - destructeur
ConfigReader::ConfigReader ()
{

}

ConfigReader::ConfigReader (const ConfigReader * reader)
{

}

ConfigReader::~ConfigReader ()
{

}

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées

//------------------------------------------------------------- Méthodes privées
