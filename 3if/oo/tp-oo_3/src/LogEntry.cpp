/*******************************************************************************
                LogEntry - Représente une ligne du fichier de log
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <LogEntry> (fichier LogEntry.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système
#include <stdexcept>

//------------------------------------------------------------ Include personnel
#include "LogEntry.h"
#include "Logger.h"

//------------------------------------------------------------------- Constantes
const std::string LogEntry::EXTERNAL_DOCUMENT = "*";
const regex LogEntry::REQUEST_URI(
        R"(^(?:\:\d+)?((?:\/(?:[^\/?]+\/)*)?([^.\/?][^\/?]+?)?(?:\.(\w*))?))"
        R"((?:((\?.*)|(;.+)))?$)"
);
const regex LogEntry::APACHE_LOG_ENTRY(
        R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}) (\S+) (\S+) )"
        R"(\[(\d{2})\/(\w{3})\/(\d{4})\:(\d{2})\:(\d{2})\:(\d{2}) )"
        R"(\+(\d{2})(\d{2})] \"([A-Z]+) ([^\"]*?)\s+HTTP\/(\d\.\d)\" (\d+) )"
        R"((\d+|\-) \"([^\"]*)\" \"([^\"]*)\"$)"
);

//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies
std::istream & operator >> (std::istream & input, LogEntry & logEntry)
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::operator >>");
    std::string line;
    std::getline(input, line);
    if (line.empty())
    {
        return input;
    }
    smatch match;
    if (!regex_match(line, match, LogEntry::APACHE_LOG_ENTRY))
    {
        throw std::runtime_error("Invalid log entry");
    }
    logEntry.hour = atoi(match[10].str().c_str());
    logEntry.requestMethod = match[15];
    logEntry.requestUri = match[16];
    logEntry.statusCode = atoi(match[18].str().c_str());
    logEntry.refererUrl = match[20];
    return input;
} //----- Fin de operator >>

//----------------------------------------------------------- Méthodes publiques
unsigned short LogEntry::GetHour () const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::GetHour");
    return hour;
} //----- Fin de GetHour

const std::string & LogEntry::GetRequestMethod () const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::GetRequestMethod");
    return requestMethod;
} //----- Fin de GetRequestMethod

const std::string LogEntry::GetRequestUriConverted () const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::GetRequestUriConverted");
    smatch match;
    if (!parseUri(requestUri, match))
    {
        return requestUri;
    }
    return match[1];
} //----- Fin de GetRequestUriConverted

const std::string LogEntry::GetRequestUriExtension () const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::GetRequestUriExtension");
    smatch match;
    if (!parseUri(requestUri, match))
    {
        return "";
    }
    return match[3];
} //----- Fin de GetRequestUriExtension

unsigned short LogEntry::GetStatusCode () const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::GetStatusCode");
    return statusCode;
} //----- Fin de GetStatusCode

const std::string LogEntry::GetRefererUrlConverted (const std::string & local)
    const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::GetRefererUrlConverted");
    if (!refererUrl.compare(0, local.size(), local))
    {
        std::string convertedUrl = refererUrl.substr(local.size());
        smatch match;
        if (!parseUri(convertedUrl, match))
        {
            return convertedUrl;
        }
        return match[1];
    }
    return EXTERNAL_DOCUMENT;
} //----- Fin de GetRefererUrlConverted

//-------------------------------------------------- Constructeurs - destructeur
LogEntry::LogEntry () :
        hour(0), requestMethod(""), requestUri(""), statusCode(0),
        refererUrl("")
// Algorithme :
{
    Logger::Debug("Appel au constructeur de LogEntry");
} //----- Fin du constructeur

LogEntry::~LogEntry ()
// Algorithme :
{
    Logger::Debug("Appel au destructeur de LogEntry");
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées
bool LogEntry::parseUri (const std::string & uri, smatch & match) const
// Algorithme :
{
    Logger::Debug("Appel à LogEntry::parseUri");
    return regex_match(uri, match, REQUEST_URI);
} //----- Fin de parseUri
