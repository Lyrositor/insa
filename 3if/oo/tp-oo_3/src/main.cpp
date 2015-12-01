/*************************************************************************
                main - Interpréteur à la ligne de commande
                             -------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>

//------------------------------------------------------ Include personnel
#include "ArgumentParser.h"

//------------------------------------------------------------- Constantes

//-------------------------------------------------------------- FONCTIONS

int main(int argc, char * argv[])
// Algorithme :
{
    string logFileName;
    string dotFileName;
    bool restrictExtensions;
    unsigned int withinHour;

    ArgumentParser* parser = new ArgumentParser();
    parser->addArgument("log");
    parser->addOption("g", ArgumentParser::STRING);
    parser->addOption("e", ArgumentParser::TOGGLE);
    parser->addOption("t", ArgumentParser::UNSIGNED_INT);

    if (!parser->parse(argc, argv))
        ;
    if (!parser->getArgument("log"))
        ;
    if (dotFileName = parser->getOption("g"))
        ;
    if (restrictExtensions = parser->getOption("e"))
        ;
    if (withinHour = parser->getOption("t"))
        ;

    return 0;
}
