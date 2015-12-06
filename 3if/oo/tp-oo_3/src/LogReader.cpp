/*******************************************************************************
                  LogReader - Lecteur de fichier de log Apache
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <LogReader> (fichier LogReader.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système
#include <stdexcept>
#include <sstream>

//------------------------------------------------------------ Include personnel
#include "LogEntry.h"
#include "Logger.h"
#include "LogReader.h"

//------------------------------------------------------------------- Constantes

//---------------------------------------------------------- Variables de classe

//----------------------------------------------------------------- Types privés


//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies

//----------------------------------------------------------- Méthodes publiques
void LogReader::Close ()
// Algorithme :
{
    Logger::Debug("Appel à LogReader::Close");
    if (logFile.is_open())
    {
        logFile.close();
    }
} //----- Fin de Close

bool LogReader::Eof ()
// Algorithme :
{
    Logger::Debug("Appel à LogReader::Eof");
    return logFile.eof();
} //----- Fin de Eof

bool LogReader::Open (std::string & filename)
// Algorithme :
{
    Logger::Debug("Appel à LogReader::Open");
    Close();
    currentLine = 0;
    logFile.open(filename);
    return logFile.is_open();
} //----- Fin de Open

void LogReader::ReadLine (LogEntry & entry)
// Algorithme :
{
    Logger::Debug("Appel à LogReader::ReadLine");
    currentLine++;
    try
    {
        logFile >> entry;
    }
    catch (std::runtime_error & e)
    {
        std::stringstream ss;
        ss << "Failed to parse line " << currentLine << " (" << e.what() << ")";
        throw std::runtime_error(ss.str());
    }
} //----- Fin de ReadLine

//------------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------------- Constructeurs - destructeur
LogReader::LogReader () : currentLine(0)
// Algorithme :
{
    Logger::Debug("Appel au constructeur de LogReader");
} //----- Fin du constructeur

LogReader::~LogReader ()
// Algorithme :
{
    Logger::Debug("Appel au destructeur de LogReader");
    Close();
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées

//------------------------------------------------------------- Méthodes privées
