/*******************************************************************************
                  Logger - Gère l'affichage de messages de log
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <Logger> (fichier Logger.h)
#if ! defined ( LOGGER_H )
#define LOGGER_H

// Définir les macros de niveau de log.
#ifdef MAP
#define DEBUG(args ...) Logger::Debug(args)
#else
#define DEBUG(args ...)
#endif // MAP
#define ERROR(args ...) Logger::Debug(args)
#define INFO(args ...) Logger::Info(args)
#define WARNING(args ...) Logger::Warning(args)

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
// Classe d'utilité pour afficher des messages sur la sortie standard. Permet de
// choisir des couleurs pour les messages.
//------------------------------------------------------------------------------

class Logger
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques

    template<typename ... ARGS> static void Debug (ARGS ... args);
    // <args> : un nombre variable d'éléments à afficher
    // Mode d'emploi : Affiche un message de niveau debug si la définition MAP
    // est active. Le préfixe "Debug: " est ajouté au message. Si les couleurs
    // sont actives, le message sera affiché en vert.

    template<typename ... ARGS> static void Error (ARGS ... args);
    // <args> : un nombre variable d'éléments à afficher
    // Mode d'emploi : Affiche un message de niveau erreur. Le préfixe "Error :"
    // est ajouté au message. Si les couleurs sont actives, le message sera
    // affiché en rouge.

    template<typename ... ARGS> static void Info (ARGS ... args);
    // <args> : un nombre variable d'éléments à afficher
    // Mode d'emploi : Affiche un message de niveau information. Le message n'a
    // aucune couleur spéciale.

    template<typename ... ARGS> static void Warning (ARGS ... args);
    // <args> : un nombre variable d'éléments à afficher
    // Mode d'emploi : Affiche un message de niveau avertissement. Le préfixe
    // "Warning: " est ajouté au message. Si les couleurs sont actives, le
    // message sera affiché en jaune.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    template<typename ... ARGS> static void log (
            std::ostream & out, TerminalColor color,
            ARGS ... args
    );
    // <out> : le flux de sortie des messages
    // <color> : la couleur du message
    // <args> : un nombre variable d'éléments à afficher
    // Mode d'emploi : Affiche un message sur le flux de sortie <out>, avec la
    // couleur <color>. Le message est constitué de la somme de tous les <args>.

    static void print (std::ostream & out);
    // <out> : le flux de sortie des messages
    // Mode d'emploi : Appelé en fin de message, effectue un retour à la ligne.

    template<typename FIRST, typename ... ARGS> static void print (
            std::ostream & out, FIRST arg1, ARGS ... args
    );
    // <out> : le flux de sortie des messages
    // <args1> : l'argument à envoyer dans le flux <out>
    // <args> : le reste des arguments à afficher par la suite
    // Mode d'emploi : S'appelle récursivement avec une liste variable
    // d'arguments. Quand il ne reste plus d'arguments, un retour à la ligne est
    // effectué.

protected:
//----------------------------------------------------------- Attributs protégés
    static const std::string P;  // Le préfixe des codes couleur
};

//-------------------------------------------------- Implémentations de <Logger>
template<typename ... ARGS> void Logger::Debug (ARGS ... args)
{
    log(std::cout, GREEN, "Debug: ", args ...);
} //----- Fin de Debug

template<typename ... ARGS> void Logger::Error (ARGS ... args)
{
    log(std::cerr, RED, "Error: ", args ...);
} //----- Fin de Error

template<typename ... ARGS> void Logger::Info (ARGS ... args)
{
    log(std::cout, NONE, args ...);
} //----- Fin de Info

template<typename ... ARGS> void Logger::Warning (ARGS ... args)
{
    log(std::cerr, YELLOW, "Warning: ", args ...);
} //----- Fin de Warning

template<typename ... ARGS>
void Logger::log (std::ostream & out, TerminalColor color, ARGS ... args)
// Algorithme : Insère les codes couleur si COLORS est actif ; sinon, affiche le
// message sans couleur.
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
// Algorithme : Affiche le premier argument, puis s'appelle récursivement
// jusqu'à ce qu'il ne reste plus d'arguments.
{
    out << arg1;
    print(out, args ...);
}; //----- Fin de print

#endif // LOGGER_H
