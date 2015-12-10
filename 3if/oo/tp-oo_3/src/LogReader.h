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
// Permet de lire un fichier de log Apache pour en extraire les données sur
// chaque ligne.
//------------------------------------------------------------------------------

class LogReader
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    void Close ();
    // Mode d'emploi : Ferme le flux de fichier associé, s'il a été ouvert. Si
    // aucun flux n'a été ouvert, aucune action n'est effectuée.

    bool Eof () const;
    // Mode d'emploi : Renvoie vrai si la fin de fichier a été atteinte.

    bool Open (const std::string & filename);
    // <filename> : le nom de fichier à ouvrir en mode lecture
    // Mode d'emploi : Ouvre un fichier de log <filename> en mode lecture.

    void ReadLine (LogEntry & entry);
    // <entry> : l'entrée à remplir d'informations
    // Mode d'emploi : Lit une ligne du fichier et remplit <entry> des
    // informations extraites de la ligne.

//------------------------------------------------------- Surcharge d'opérateurs
    LogReader & operator = (const LogReader & reader) = delete;
    // <reader> : le lecteur à copier
    // Mode d'emploi : Supprimé. La copie est interdite pour éviter d'avoir des
    // conflits liés aux flux.

//-------------------------------------------------- Constructeurs - destructeur
    LogReader ();
    // Mode d'emploi : Initialise un lecteur sans flux ouvert.

    LogReader (const LogReader & reader) = delete;
    // <reader> : le lecteur à copier
    // Mode d'emploi : Supprimé. La copie est interdite pour éviter d'avoir des
    // conflits liés aux flux.

    virtual ~LogReader ();
    // Mode d'emploi : Supprime le lecteur et ferme tout flux de fichier
    // associé.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs protégés
    std::ifstream logFile;  // Le flux de fichier d'entrée associé
    int currentLine;  // Le numéro de la ligne actuelle de lecture
};

#endif // LOG_READER_H
