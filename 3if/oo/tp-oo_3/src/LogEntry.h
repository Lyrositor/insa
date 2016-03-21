/*******************************************************************************
                LogEntry - Représente une ligne du fichier de log
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <LogEntry> (fichier LogEntry.h)
#if ! defined ( LOG_ENTRY_H )
#define LOG_ENTRY_H

//--------------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <set>
#include <string>

// Utilisation de Boost si disponible, par souci de performance ; sinon, la
// bibliothèque regex de la STL est utilisée, par défaut.
#ifdef USE_BOOST
#include <boost/regex.hpp>
using boost::regex;
using boost::regex_match;
using boost::smatch;
#else
#include <regex>
using std::regex;
using std::regex_match;
using std::smatch;
#endif

//------------------------------------------------------------------------------
// Rôle de la classe <LogEntry>
// Représente une entrée dans un fichier de log Apache.
//------------------------------------------------------------------------------

class LogEntry
{
//----------------------------------------------------------------------- PUBLIC
public:
//-------------------------------------------------------------- Fonctions amies
    friend std::istream & operator >> (
            std::istream & input, LogEntry & logEntry
    );
    // <input> : le flux d'entrée d'un fichier de log Apache
    // <logEntry> : l'entrée de log à remplir
    // Mode d'emploi : Permet de lire des entrées de log directement à partir
    // d'un flux, en extrayant les données importantes d'une ligne du fichier.

//----------------------------------------------------------- Méthodes publiques
    unsigned short GetHour () const;
    // Mode d'emploi : Renvoie l'heure de génération de l'entrée de log.

    const std::string & GetRequestMethod () const;
    // Mode d'emploi : Renvoie la méthode HTTP de requête du document.

    const std::string GetRequestUriConverted () const;
    // Mode d'emploi : Renvoie l'URI du document demandé par la requête HTTP.

    const std::string GetRequestUriExtension () const;
    // Mode d'emploi : Renvoie l'extension du document demandé. Si l'extension
    // ne peut être déduite, renvoie une chaîne vide.

    unsigned short GetStatusCode () const;
    // Mode d'emploi : Renvoie le statut de la requête.

    const std::string GetRefererUrlConverted (const std::string & local) const;
    // <local> : l'URL du serveur local
    // Mode d'emploi : Renvoie l'URL du référant de la requête. Si l'URL
    // commence par <local>, la requête vient du serveur local, et le préfixe
    // <local> est enlevé à l'URL.

//-------------------------------------------------- Constructeurs - destructeur
    LogEntry ();
    // Mode d'emploi : Construit une nouvelle entrée vide.

    virtual ~LogEntry ();
    // Mode d'emploi : Détruit l'entrée.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    bool parseUri (const std::string & uri, smatch & match) const;
    // <uri> : l'URI à analyser
    // <match> : le résultat de l'examination, à modifier
    // Mode d'emploi : Examine une URI pour en extraire les informations
    // intéressantes.

protected:
//----------------------------------------------------------- Attributs protégés
    unsigned short hour;  // L'heure de génération de la requête
    std::string requestMethod;  // La méthode de requête HTTP
    std::string requestUri;  // L'URI du document demandé
    unsigned short statusCode;  // Le statut de la requête
    std::string refererUrl;  // L'URL du référant de la requête

    static const std::string EXTERNAL_DOCUMENT;  // L'étiquette spéciale pour
                                                 // les documents externes
    static const regex APACHE_LOG_ENTRY;  // Le regex pour une ligne du log
    static const regex REQUEST_URI;  // Le regex pour traiter une URI
};

#endif // LOG_ENTRY_H
