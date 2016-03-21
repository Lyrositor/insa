/*******************************************************************************
               ConfigReader - Lecteur de fichier de configuration
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <ConfigReader> (fichier ConfigReader.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <sstream>

//------------------------------------------------------------ Include personnel
#include "ConfigReader.h"
#include "Logger.h"

//----------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Méthodes publiques
int ConfigReader::GetInteger (const std::string & key, int def) const
// Algorithme : Trouve la valeur désirée si elle existe, puis la convertit en
// entier.
{
    try
    {
        return atoi(config.at(key).c_str());

    }
    catch (std::out_of_range & e)
    {
        return def;
    }
}

std::unordered_set<std::string> ConfigReader::GetSet (
        const std::string & key, const std::unordered_set<std::string> & def
) const
// Algorithme : Trouve la valeur désirée si elle existe, puis sépare la valeur
// stockée selon les virgules.
{
    try
    {
        std::stringstream ss(config.at(key));
        std::unordered_set<std::string> elems;
        std::string item;
        while (std::getline(ss, item, ','))
        {
            elems.insert(item);
        }
        return elems;
    }
    catch (std::out_of_range & e)
    {
        return def;
    }
}

std::string ConfigReader::GetString (
        const std::string & key, const std::string & def
) const
{
    try
    {
        return config.at(key);
    }
    catch (std::out_of_range & e)
    {
        return def;
    }
}

//-------------------------------------------------- Constructeurs - destructeur
ConfigReader::ConfigReader (const std::string & filename)
// Algorithme : Lit un fichier de configuration ligne par ligne et en extrait
// la clé et la valeur, puis ferme le flux de fichier.
{
    DEBUG("Appel au constructeur de ConfigReader");
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        return;
    }

    while (!std::getline(file, line).eof())
    {
        if (line.empty())
        {
            continue;
        }
        std::string param;
        std::string value;

        unsigned long posEqual = line.find('=');
        param = line.substr(0, posEqual);
        value = line.substr(posEqual + 1);
        config[param] = value;
    }

    file.close();

} //----- Fin du constructeur

ConfigReader::~ConfigReader ()
{
    DEBUG("Appel au destructeur de ConfigReader");
} //----- Fin du destructeur
