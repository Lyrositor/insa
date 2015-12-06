/*******************************************************************************
                Document - Représente un document sur le serveur
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <Document> (fichier Document.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système

//------------------------------------------------------------ Include personnel
#include "Document.h"
#include "Logger.h"

//------------------------------------------------------------------- Constantes

//---------------------------------------------------------- Variables de classe

//----------------------------------------------------------------- Types privés


//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies

//----------------------------------------------------------- Méthodes publiques
void Document::AddLocalHit ()
// Algorithme :
{
    Logger::Debug("Appel à Document::AddLocalHit");
    localHits++;
} //----- Fin de AddLocalHit

void Document::AddRemoteHit (unsigned long documentId)
// Algorithme :
{
    Logger::Debug("Appel à Document::AddRemoteHit");
    if (!remoteHits.count(documentId))
    {
        remoteHits[documentId] = 0;
    }
    remoteHits[documentId]++;
} //----- Fin de AddRemoteHit

unsigned int Document::GetLocalHits () const
// Algorithme :
{
    Logger::Debug("Appel à Document::GetLocalHits");
    return localHits;
} //----- Fin de GetLocalHits

const std::unordered_map<unsigned long, unsigned int> & Document::GetRemoteHits
        () const
// Algorithme :
{
    Logger::Debug("Appel à Document::GetRemoteHits");
    return remoteHits;
} //----- Fin de GetRemoteHits

const std::string & Document::GetUri () const
// Algorithme :
{
    Logger::Debug("Appel à Document::GetUri");
    return uri;
} //----- Fin de GetUri

//------------------------------------------------------- Surcharge d'opérateurs
Document & Document::operator = (const Document & document)
// Algorithme :
{
    Logger::Debug("Appel à Document::operator =");
    localHits = document.localHits;
    remoteHits = document.remoteHits;
    uri = document.uri;
    return *this;
} //----- Fin de la surcharge d'opérateur =

bool Document::operator > (const Document & document) const
// Algorithme :
{
    Logger::Debug("Appel à Document::operator >");
    return localHits > document.localHits;
} //----- Fin de la surcharge d'opérateur >

//-------------------------------------------------- Constructeurs - destructeur
Document::Document (const std::string & documentUri) :
        localHits(0), uri(documentUri)
// Algorithme :
{
    Logger::Debug("Appel au constructeur de Document");
} //----- Fin du constructeur

Document::Document (const Document & document)
// Algorithme :
{
    Logger::Debug("Appel au constructeur de copie de Document");
    localHits = document.localHits;
    remoteHits = document.remoteHits;
    uri = document.uri;
} //----- Fin du constructeur de copie

Document::~Document()
// Algorithme :
{
    Logger::Debug("Appel au destructeur de Document");
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées

//------------------------------------------------------------- Méthodes privées
