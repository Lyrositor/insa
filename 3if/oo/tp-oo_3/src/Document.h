/*******************************************************************************
                Document - Représente un document sur le serveur
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <Document> (fichier Document.h)
#if ! defined ( DOCUMENT_H )
#define DOCUMENT_H

//--------------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>

//------------------------------------------------------------------- Constantes

//------------------------------------------------------------------------ Types

//------------------------------------------------------------------------------
// Rôle de la classe <Document>
//
//------------------------------------------------------------------------------

class Document
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    void AddLocalHit ();
    // Mode d'emploi :

    void AddRemoteHit (unsigned long documentId);
    // Mode d'emploi :

    unsigned int GetLocalHits () const;
    // Mode d'emploi :

    const std::unordered_map<unsigned long, unsigned int> & GetRemoteHits ()
            const;
    // Mode d'emploi :

    const std::string & GetUri () const;
    // Mode d'emploi :

//------------------------------------------------------- Surcharge d'opérateurs
    Document & operator = (const Document & document);
    // Mode d'emploi :

    bool operator > (const Document & document) const;
    // Mode d'emploi :

//-------------------------------------------------- Constructeurs - destructeur
    Document (const std::string & documentUri);
    // Mode d'emploi :

    Document (const Document & document);
    // Mode d'emploi :

    virtual ~Document ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------------- Attributs protégés
    unsigned int localHits;
    std::unordered_map<unsigned long, unsigned int> remoteHits;
    std::string uri;

private:
//------------------------------------------------------------- Attributs privés

//---------------------------------------------------------------- Classes amies

//-------------------------------------------------------------- Classes privées

//----------------------------------------------------------------- Types privés
};

//----------------------------------------------- Types dépendants de <Document>


#endif // DOCUMENT_H
