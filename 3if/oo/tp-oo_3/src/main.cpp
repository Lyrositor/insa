/*******************************************************************************
                   main - Interpréteur à la ligne de commande
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système
using namespace std;
#include <list>
#include <string>
#include <tclap/CmdLine.h>
#include <unordered_set>

//------------------------------------------------------------ Include personnel
#include "DotFileWriter.h"
#include "HistoryManager.h"
#include "Logger.h"
#include "LogReader.h"

//------------------------------------------------------------------- Constantes
const string DESCRIPTION = "Parser for Apache logs";
const string VERSION = "1.0";

const unordered_set<string> DEFAULT_EXCLUDED_EXTENSIONS = {
        // Images
        "art", "bm", "bmp", "dwg", "dxf", "fig", "flo", "fpx", "g3", "gif",
        "ico", "ief", "iefs", "jfif", "jfif-tbnl", "jpe", "jpeg", "jpg", "jps",
        "jut", "mcf", "nap", "naplps", "nif", "niff", "pbm", "pct", "pcx",
        "pgm", "pic", "pict", "pm", "png", "pnm", "ppm", "qif", "qti", "qtif",
        "ras", "rast", "rf", "rgb", "rp", "svg", "svf", "tif", "tiff", "turbot",
        "wbmp", "xbm", "xif", "xpm", "xwd",
        // CSS
        "css",
        // JavaScript
        "js"
};
const string DEFAULT_LOCAL_URL = "http://intranet-if.insa-lyon.fr";
const unsigned int DEFAULT_MAX_DOCUMENTS = 10;

//-------------------------------------------------------------------- FONCTIONS
int main (int argc, const char * const * argv)
// Algorithme :
{
    string logFilename;
    LogReader* logFile = nullptr;
    string dotFilename;
    DotFileWriter* dotFile = nullptr;
    unordered_set<string> excludedExtensions;
    unsigned int startHour = 0, endHour = 24;

    // Désactiver la synchronization avec la bibliothèque IO de C.
    cout.sync_with_stdio(false);

    // Initialiser le parseur d'arguments.
    TCLAP::CmdLine cmd(DESCRIPTION, ' ', VERSION);

    // Configurer l'argument du chemin de fichier log.
    TCLAP::UnlabeledValueArg<string> logFilenameArg(
            "log", "path to the Apache log file to parse", true, "", "FILE",
            cmd
    );

    // Configurer l'argument (optionnel) du chemin de fichier dot-file, pour
    // la génération d'un graphe Graphviz.
    TCLAP::ValueArg<string> dotFilenameArg(
            "g", "graphviz", "path to a Graphviz file to generate", false, "",
            "FILE", cmd
    );

    TCLAP::SwitchArg excludeExtensionsArg(
            "e", "exclude", "exclude restricted extensions", cmd, false
    );

    // Configurer l'argument (optionnel) de restriction de la plage horaire.
    // Seules des valeurs comprises entre 0 et 23 (incluses) sont acceptées.
    vector<unsigned int> allowedHours;
    for (unsigned int i = 0; i < 24; i++)
    {
        allowedHours.push_back(i);
    }
    TCLAP::ValuesConstraint<unsigned int> timeVals( allowedHours );
    TCLAP::ValueArg<unsigned int> timeArg(
            "t", "time", "restrict parsing to the specified hour", false,
            0, &timeVals, cmd
    );

    // Récupérer les valeurs des arguments à la ligne de commande.
    try
    {
        cmd.parse(argc, argv);

        // Essayer de lire le fichier de log.
        logFilename = logFilenameArg.getValue();
        logFile = new LogReader();
        if (!logFile->Open(logFilename))
        {
            Logger::Error("Failed to open log file for reading");
            delete logFile;
            return 1;
        }

        // Essayer de lire le DOT-file, si demandé.
        if (dotFilenameArg.isSet())
        {
            dotFilename = dotFilenameArg.getValue();
            dotFile = new DotFileWriter();
            if (!dotFile->Open(dotFilename))
            {
                Logger::Error("Failed to open DOT file for writing");
                delete dotFile;
                delete logFile;
                return 1;
            }
        }

        // Enregistrer les extensions à exclure de la lecture du log.
        if (excludeExtensionsArg.getValue())
        {
            excludedExtensions = DEFAULT_EXCLUDED_EXTENSIONS;
        }

        // Restreindre la plage horaire autorisée, si demandée.
        if (timeArg.isSet())
        {
            startHour = timeArg.getValue();
            endHour = startHour + 1;
            Logger::Warning(
                    "Only hits between ", startHour, "h and ", endHour,
                    "h have been taken into account."
            );
        }
    }
    catch (TCLAP::ArgException & e)
    {
        Logger::Error(e.what());
        delete logFile;
        delete dotFile;
        return 1;
    }

    // Peupler l'historique de documents à partir du fichier log.
    HistoryManager historyMgr(DEFAULT_LOCAL_URL);
    bool loaded = historyMgr.FromFile(
            logFile, excludedExtensions, startHour, endHour
    );
    logFile->Close();
    delete logFile;
    if (!loaded)
    {
        Logger::Error("Failed to parse log file");
        delete dotFile;
        return 1;
    }

    // Générer le dot-file, si demandé.
    if (dotFilenameArg.isSet())
    {
        historyMgr.ToDotFile(dotFile);
        dotFile->Close();
        delete dotFile;
        Logger::Info("Dot-file ", dotFilename, " generated");
    }

    // Afficher les documents les plus populaires.
    historyMgr.ListDocuments(DEFAULT_MAX_DOCUMENTS);

    return 0;
}
