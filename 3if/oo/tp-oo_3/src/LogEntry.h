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
#include <boost/regex.hpp>
#include <iostream>
#include <set>
#include <string>

//------------------------------------------------------------------- Constantes

//------------------------------------------------------------------------ Types

//------------------------------------------------------------------------------
// Rôle de la classe <LogEntry>
//
//------------------------------------------------------------------------------

class LogEntry
{
//----------------------------------------------------------------------- PUBLIC
public:
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

//------------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------------- Constructeurs - destructeur
    LogEntry ();
    // Mode d'emploi :

    virtual ~LogEntry ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    bool parseUri (const std::string & uri, boost::smatch & match) const;

private:
//------------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------------- Attributs protégés
    static const std::string EXTERNAL_DOCUMENT;
    static const boost::regex APACHE_LOG_ENTRY;
    static const boost::regex REQUEST_URI;

    unsigned short hour;
    std::string requestMethod;
    std::string requestUri;
    unsigned short statusCode;
    std::string refererUrl;

private:
//------------------------------------------------------------- Attributs privés

//---------------------------------------------------------------- Classes amies
    friend std::istream & operator >> (
            std::istream & input, LogEntry & logEntry
    );

//-------------------------------------------------------------- Classes privées

//----------------------------------------------------------------- Types privés
};

//----------------------------------------------- Types dépendants de <LogEntry>

#endif // LOG_ENTRY_H
