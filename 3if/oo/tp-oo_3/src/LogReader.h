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

//------------------------------------------------------------------- Constantes

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

    bool Eof ();
    // Mode d'emploi :

    bool Open (std::string & filename);
    // Mode d'emploi :

    void ReadLine (LogEntry & entry);
    // Mode d'emploi :

//------------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------------- Constructeurs - destructeur
    LogReader ();
    // Mode d'emploi :

    virtual ~LogReader ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------------- Attributs protégés
    std::ifstream logFile;
    int currentLine;

private:
//------------------------------------------------------------- Attributs privés

//---------------------------------------------------------------- Classes amies

//-------------------------------------------------------------- Classes privées

//----------------------------------------------------------------- Types privés
};

//---------------------------------------------- Types dépendants de <LogReader>

#endif // LOG_READER_H
