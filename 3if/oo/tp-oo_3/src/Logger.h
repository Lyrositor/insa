/*******************************************************************************
                  Logger - Gère l'affichage de messages de log
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <Logger> (fichier Logger.h)
#if ! defined ( LOGGER_H )
#define LOGGER_H

//--------------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>

//------------------------------------------------------------------------ Types
enum TerminalColor
{
    NONE = 0,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

//------------------------------------------------------------------------------
// Rôle de la classe <Logger>
//
//------------------------------------------------------------------------------

class Logger
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques

    template<typename ... ARGS> static void Debug (ARGS ... args);
    // Mode d'emploi :

    template<typename ... ARGS> static void Error (ARGS ... args);
    // Mode d'emploi :

    template<typename ... ARGS> static void Info (ARGS ... args);
    // Mode d'emploi :

    template<typename ... ARGS> static void Warning (ARGS ... args);
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    template<typename ... ARGS> static void log (
            std::ostream & out, TerminalColor color,
            ARGS ... args
    );
    // Mode d'emploi :

    static void print (std::ostream & out);
    // Mode d'emploi :

    template<typename FIRST, typename ... ARGS> static void print (
            std::ostream & out, FIRST arg1, ARGS ... args
    );
    // Mode d'emploi :

protected:
//----------------------------------------------------------- Attributs protégés
    static const std::string P;
};

//-------------------------------------------------- Implémentations de <Logger>
template<typename ... ARGS> void Logger::Debug (ARGS ... args)
// Algorithme :
{
#ifdef MAP
    log(std::cout, GREEN, "Debug: ", args ...);
#endif // MAP
} //----- Fin de Debug

template<typename ... ARGS> void Logger::Error (ARGS ... args)
// Algorithme :
{
    log(std::cerr, RED, "Error: ", args ...);
} //----- Fin de Error

template<typename ... ARGS> void Logger::Info (ARGS ... args)
// Algorithme :
{
    log(std::cout, NONE, args ...);
} //----- Fin de Info

template<typename ... ARGS> void Logger::Warning (ARGS ... args)
// Algorithme :
{
    log(std::cerr, YELLOW, "Warning: ", args ...);
} //----- Fin de Warning

template<typename ... ARGS>
void Logger::log (std::ostream & out, TerminalColor color, ARGS ... args)
// Algorithme :
{
#ifdef COLORS
    if (color == NONE)
    {
#endif // COLORS
        print(out, args ...);
#ifdef COLORS
    }
    else
    {
        print(out, P, 29 + color, "m", args ..., P, "0m");
    }
#endif // COLORS
} //----- Fin de log

template<typename FIRST, typename ... ARGS>
void Logger::print (std::ostream & out, FIRST arg1, ARGS ... args)
// Algorithme :
{
    out << arg1;
    print(out, args ...);
}; //----- Fin de print

#endif // LOGGER_H
