/*******************************************************************************
               ConfigReader - Lecteur de fichier de configuration
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <ConfigReader> (fichier ConfigReader.h)
#if ! defined ( CONFIG_READER_H )
#define CONFIG_READER_H

//--------------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <unordered_set>

//------------------------------------------------------------------------------
// Rôle de la classe <ConfigReader>
// Lit un fichier de configuration et permet d'en extraire les associations
// clés -> valeurs. Un fichier de configuration est structuré de la manière
// suivante :
// cle1=valeur1
// cle2=valeur2
//------------------------------------------------------------------------------

class ConfigReader
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    int GetInteger (const std::string & key, int def = 0) const;
    // <key> : la clé associée à la valeur désirée
    // <def> : la valeur par défaut à utiliser
    // Mode d'emploi : Essaie de trouver la clé <key>. Si elle existe, renvoie
    // la valeur associée convertie en entier ; sinon, renvoie la valeur par
    // défaut <def>.

    std::unordered_set<std::string> GetSet (
            const std::string & key, const std::unordered_set<std::string> & def
    ) const;
    // <key> : la clé associée à la valeur désirée
    // <def> : la valeur par défaut à utiliser
    // Mode d'emploi : Essaie de trouver la clé <key>. Si elle existe, renvoie
    // la valeur associée convertie en set ; sinon, renvoie la valeur par défaut
    // <def>.

    std::string GetString (const std::string & key, const std::string & def = ""
    ) const;
    // <key> : la clé associée à la valeur désirée
    // <def> : la valeur par défaut à utiliser
    // Mode d'emploi : Essaie de trouver la clé <key>. Si elle existe, renvoie
    // la valeur associée ; sinon, renvoie la valeur par défaut <def>.

//------------------------------------------------------- Surcharge d'opérateurs
    ConfigReader & operator = (const ConfigReader & reader) = delete;
    // <reader> : le lecteur à copier
    // Mode d'emploi : Supprimé. La copie est interdite pour éviter d'avoir des
    // conflits liés aux flux.

//-------------------------------------------------- Constructeurs - destructeur
    ConfigReader (const std::string & filename);
    // <filename> : le nom du fichier de configuration à lire
    // Mode d'emploi : Initialise le lecteur à partir du fichier de
    // configuration spécifié par <filename>.

    ConfigReader (const ConfigReader & reader) = delete;
    // <reader> : le lecteur à copier
    // Mode d'emploi : Supprimé. La copie est interdite pour éviter d'avoir des
    // conflits liés aux flux.

    virtual ~ConfigReader ();
    // Mode d'emploi : Détruit le lecteur.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs protégés
    std::unordered_map<std::string, std::string> config;
};

#endif // CONFIG_READER_H
