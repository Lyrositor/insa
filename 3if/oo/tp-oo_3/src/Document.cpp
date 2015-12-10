/*******************************************************************************
                Document - Représente un document sur le serveur
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <Document> (fichier Document.cpp)

//---------------------------------------------------------------------- INCLUDE

//------------------------------------------------------------ Include personnel
#include "Document.h"
#include "Logger.h"

//----------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Méthodes publiques
void Document::AddLocalHit ()
{
    Logger::Debug("Appel à Document::AddLocalHit");
    localHits++;
} //----- Fin de AddLocalHit

void Document::AddRemoteHit (unsigned long documentId)
// Algorithme : Crée une case pour le document si elle n'existe pas déjà, puis
// incrémente le compteur dans cette case de 1.
{
    Logger::Debug("Appel à Document::AddRemoteHit");
    if (!remoteHits.count(documentId))
    {
        remoteHits[documentId] = 0;
    }
    remoteHits[documentId]++;
} //----- Fin de AddRemoteHit

unsigned int Document::GetLocalHits () const
{
    Logger::Debug("Appel à Document::GetLocalHits");
    return localHits;
} //----- Fin de GetLocalHits

const DocumentHits & Document::GetRemoteHits () const
{
    Logger::Debug("Appel à Document::GetRemoteHits");
    return remoteHits;
} //----- Fin de GetRemoteHits

const std::string & Document::GetUri () const
{
    Logger::Debug("Appel à Document::GetUri");
    return uri;
} //----- Fin de GetUri

//------------------------------------------------------- Surcharge d'opérateurs
bool Document::operator > (const Document & document) const
{
    Logger::Debug("Appel à Document::operator >");
    return localHits > document.localHits;
} //----- Fin de la surcharge d'opérateur >

//-------------------------------------------------- Constructeurs - destructeur
Document::Document (const std::string & documentUri) :
        localHits(0), uri(documentUri)
{
    Logger::Debug("Appel au constructeur de Document");
} //----- Fin du constructeur

Document::~Document()
{
    Logger::Debug("Appel au destructeur de Document");
} //----- Fin du destructeur
