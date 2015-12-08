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
//
//------------------------------------------------------------------------------

class LogEntry
{
//----------------------------------------------------------------------- PUBLIC
public:
//-------------------------------------------------------------- Fonctions amies
    friend std::istream & operator >> (
            std::istream & input, LogEntry & logEntry
    );

//----------------------------------------------------------- Méthodes publiques
    unsigned short GetHour () const;
    // Mode d'emploi :

    const std::string & GetRequestMethod () const;
    // Mode d'emploi :

    const std::string GetRequestUriConverted () const;
    // Mode d'emploi :

    const std::string GetRequestUriExtension () const;
    // Mode d'emploi :

    unsigned short GetStatusCode () const;
    // Mode d'emploi :

    const std::string GetRefererUrlConverted (const std::string & local)
            const;
    // Mode d'emploi :

//-------------------------------------------------- Constructeurs - destructeur
    LogEntry ();
    // Mode d'emploi :

    virtual ~LogEntry ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    bool parseUri (const std::string & uri, smatch & match) const;

protected:
//----------------------------------------------------------- Attributs protégés
    unsigned short hour;
    std::string requestMethod;
    std::string requestUri;
    unsigned short statusCode;
    std::string refererUrl;

    static const std::string EXTERNAL_DOCUMENT;
    static const regex APACHE_LOG_ENTRY;
    static const regex REQUEST_URI;
};

#endif // LOG_ENTRY_H
