/*******************************************************************************
            HistoryManager - Gère un graphe de parcours d'un serveur
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <HistoryManager> (fichier HistoryManager.h)
#if ! defined ( HISTORY_MANAGER_H )
#define HISTORY_MANAGER_H

//--------------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//------------------------------------------------------------------- Constantes

//------------------------------------------------------------------------ Types
class Document;
class DotFileWriter;
class LogEntry;
class LogReader;

typedef std::vector<Document> Documents;

//------------------------------------------------------------------------------
// Rôle de la classe <HistoryManager>
//
//------------------------------------------------------------------------------

class HistoryManager
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    bool FromFile (
            LogReader * logFile,
            const std::unordered_set<std::string> & excludedExtensions,
            unsigned int startHour,
            unsigned int endHour
    );
    // Mode d'emploi :

    void ListDocuments (unsigned int max) const;
    // Mode d'emploi :

    void ToDotFile (DotFileWriter * dotFile) const;
    // Mode d'emploi :


//------------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------------- Constructeurs - destructeur
    HistoryManager (const std::string & serverUrl);
    // Mode d'emploi :

    virtual ~HistoryManager ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    void addEntry (const LogEntry & entry);
    // Mode d'emploi :

private:
//------------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------------- Attributs protégés
    Documents documents;
    std::unordered_map<std::string, Documents::size_type> documentsByName;
    const std::string localServerUrl;

private:
//------------------------------------------------------------- Attributs privés

//---------------------------------------------------------------- Classes amies

//-------------------------------------------------------------- Classes privées

//----------------------------------------------------------------- Types privés
};

//----------------------------------------- Types dépendants de <HistoryManager>

#endif // HISTORY_MANAGER_H
