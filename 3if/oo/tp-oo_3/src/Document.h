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

//------------------------------------------------------------------------ Types
typedef std::unordered_map<unsigned long, unsigned int> DocumentHits;

//------------------------------------------------------------------------------
// Rôle de la classe <Document>
// Un <Document> représente un document sur le serveur local. La classe stocke
// le nombre de fois que le document a été atteint, soit à partir d'un autre
// document sur le serveur loca, soit à partir d'un site extérieur ou inconnu.
// Note : il existe un document spécial (avec pour URI "*") qui représente
// l'extérieur. Celui-ci ne devrait jamais être atteint, et peut seulement être
// une source d'accès au serveur local.
//------------------------------------------------------------------------------

class Document
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    void AddLocalHit ();
    // Mode d'emploi : Incrémente le nombre de fois que ce document a été
    // atteint par d'autres documents, ce qui inclut des documents externes.

    void AddRemoteHit (unsigned long documentId);
    // <documentId> : l'ID du document que ce document a atteint
    // Mode d'emploi : Incrémente le nombre de fois que le document <documentId>
    // a été atteint par ce document. Si le document <documentId> n'avait jamais
    // été atteint, le compte est initialisé à 1.
    // Contrat : <documentId> doit être un index dans le vecteur <documents> de
    // HistoryManager.

    unsigned int GetLocalHits () const;
    // Mode d'emploi : Renvoie le nombre de fois que ce document a été atteint.

    const DocumentHits & GetRemoteHits () const;
    // Mode d'emploi : Renvoie une liste associative de documents (identifiés
    // par leur ID) et du nombre de fois qu'ils ont été atteints par celui-ci.
    // Si un document n'est pas dans la liste, il n'a jamais été atteint par ce
    // document.

    const std::string & GetUri () const;
    // Mode d'emploi : Renvoie l'URI correspondant au document. À noter que les
    // paramètres (énumérés après l'extension, généralement en commençant par un
    // ?) ne sont pas pris en compte : index.php est le même document que
    // index.php?p=1. Si l'URI renvoyée est égale à "*", le "document" n'est pas
    // un vrai document, mais représente tous les documents externes, qui ne
    // sont pas sur le serveur local.

//------------------------------------------------------- Surcharge d'opérateurs
    bool operator > (const Document & document) const;
    // <document> : le document auquel comparer ce document
    // Mode d'emploi : Renvoie vrai si ce document a été atteint plus de fois
    // que l'autre document, et faux sinon.

//-------------------------------------------------- Constructeurs - destructeur
    Document (const std::string & documentUri);
    // <documentUri> : l'URI identifiant ce document (sans paramètres)
    // Mode d'emploi : Crée un nouveau document à partir de son URI,
    // préalablement épurée de ses paramètres (les informations variables qui
    // peuvent suivre l'extension de fichier, généralement précédées d'un ?).

    virtual ~Document ();
    // Mode d'emploi : détruit le document.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs protégés
    unsigned int localHits;  // Le nombre de fois que le document a été atteint
    DocumentHits remoteHits;  // Le nombre de fois que d'autres documents
    std::string uri;  // L'URI de ce document, relatif au serveur local
};

#endif // DOCUMENT_H
