/*******************************************************************************
                      DotFileWriter - Écrivain de DOT-file
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <DotFileWriter> (fichier DotFileWriter.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système

//------------------------------------------------------------ Include personnel
#include "DotFileWriter.h"
#include "Logger.h"

//------------------------------------------------------------------- Constantes
const std::string DotFileWriter::HEADER = "digraph {\n";
const std::string DotFileWriter::FOOTER = "}\n";

//---------------------------------------------------------- Variables de classe

//----------------------------------------------------------------- Types privés


//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies

//----------------------------------------------------------- Méthodes publiques
void DotFileWriter::AddLink (
        unsigned long sourceId, unsigned long targetId,
        const std::string & linkLabel
)
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::AddLink");
    links.push_front({sourceId, targetId, linkLabel});
} //----- Fin de AddLink

void DotFileWriter::AddNode (unsigned long id, const std::string & label)
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::AddNode");
    nodes[id] = label;
} //----- Fin de AddNode

void DotFileWriter::Close ()
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::Close");
    if (dotFile.is_open())
    {
        dotFile.close();
    }
} //----- Fin de Close

void DotFileWriter::InitGraph (unsigned long graphNodes)
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::InitGraph");
    if (nodes != nullptr)
    {
        delete[] nodes;
    }
    numNodes = graphNodes;
    nodes = new std::string[numNodes];
} //----- Fin de InitGraph

bool DotFileWriter::Open (const std::string & filename)
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::Open");
    Close();
    dotFile.open(filename);
    return dotFile.is_open();
} //----- Fin de Open

void DotFileWriter::Write ()
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::Write");
    dotFile << HEADER;
    for (unsigned int i = 0; i < numNodes; i++)
    {
        dotFile << "node" << i << " [label=\"";
        writeEscaped(nodes[i]);
        dotFile << "\"];\n";
    }
    for (Link & link : links)
    {
        dotFile << "node" << link.sourceNodeId << " -> node" <<
                link.destinationNodeId << " [label=\"";
        writeEscaped(link.label);
        dotFile << "\"];\n";
    }
    dotFile << FOOTER;
} //----- Fin de Write

//------------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------------- Constructeurs - destructeur
DotFileWriter::DotFileWriter () : nodes(nullptr), numNodes(0)
// Algorithme :
{
    Logger::Debug("Appel au constructeur de DotFileWriter");
} //----- Fin du constructeur

DotFileWriter::~DotFileWriter ()
// Algorithme :
{
    Logger::Debug("Appel au destructeur de DotFileWriter");
    if (nodes != nullptr)
    {
        delete[] nodes;
    }
    Close();
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées
void DotFileWriter::writeEscaped (const std::string & s)
// Algorithme :
{
    Logger::Debug("Appel à DotFileWriter::writeEscaped");
    for (unsigned int i = 0; i < s.length(); i++)
    {
        switch (s[i])
        {
            case '"': // Aucun break car les " et les \ doivent tous deux être
                // echappés.
            case '\\':
                dotFile << '\\';
            default:
                dotFile << s[i];
                break;
        }
    }
} //----- Fin de writeEscaped

//------------------------------------------------------------- Méthodes privées

