/*******************************************************************************
                  LogReader - Lecteur de fichier de log Apache
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <LogReader> (fichier LogReader.h)
#if ! defined ( LOG_READER_H )
#define LOG_READER_H

//--------------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <string>

//------------------------------------------------------------------------ Types
class LogEntry;

//------------------------------------------------------------------------------
// Rôle de la classe <LogReader>
//
//------------------------------------------------------------------------------

class LogReader
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    void Close ();
    // Mode d'emploi :

    bool Eof () const;
    // Mode d'emploi :

    bool Open (std::string & filename);
    // Mode d'emploi :

    void ReadLine (LogEntry & entry);
    // Mode d'emploi :

//------------------------------------------------------- Surcharge d'opérateurs
    LogReader & operator = (const LogReader & reader) = delete;
    // Mode d'emploi :

//-------------------------------------------------- Constructeurs - destructeur
    LogReader ();
    // Mode d'emploi :

    LogReader (const LogReader & reader) = delete;
    // Mode d'emploi :

    virtual ~LogReader ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs protégés
    std::ifstream logFile;
    int currentLine;
};

#endif // LOG_READER_H
