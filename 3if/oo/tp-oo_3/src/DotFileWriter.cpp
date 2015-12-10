/*******************************************************************************
                      DotFileWriter - Écrivain de DOT-file
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <DotFileWriter> (fichier DotFileWriter.cpp)

//---------------------------------------------------------------------- INCLUDE

//------------------------------------------------------------ Include personnel
#include "DotFileWriter.h"
#include "Logger.h"

//------------------------------------------------------------------- Constantes
const std::string DotFileWriter::HEADER = "digraph {\n";
const std::string DotFileWriter::FOOTER = "}\n";

//----------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- Méthodes publiques
void DotFileWriter::AddLink (
        unsigned long sourceId, unsigned long targetId,
        const std::string & linkLabel
)
{
    Logger::Debug("Appel à DotFileWriter::AddLink");
    links.push_front({sourceId, targetId, linkLabel});
} //----- Fin de AddLink

void DotFileWriter::AddNode (unsigned long id, const std::string & label)
{
    Logger::Debug("Appel à DotFileWriter::AddNode");
    nodes[id] = label;
} //----- Fin de AddNode

void DotFileWriter::Close ()
{
    Logger::Debug("Appel à DotFileWriter::Close");
    if (dotFile.is_open())
    {
        dotFile.close();
    }
} //----- Fin de Close

void DotFileWriter::InitGraph (unsigned long graphNodes)
// Algorithme : Supprime tout ancien graphe qui avait été créé en détruisant
// tous ses noeuds et en réinitialisant la liste de liens, puis prépare un
// nouveau tableau de noeuds.
{
    Logger::Debug("Appel à DotFileWriter::InitGraph");
    if (nodes != nullptr)
    {
        links.clear();
        delete[] nodes;
    }
    numNodes = graphNodes;
    nodes = new std::string[numNodes];
} //----- Fin de InitGraph

bool DotFileWriter::Open (const std::string & filename)
// Algorithme : Ferme tout flux déjà ouvert et ouvre un nouveau lié au fichier
// <filename>.
{
    Logger::Debug("Appel à DotFileWriter::Open");
    Close();
    dotFile.open(filename);
    return dotFile.is_open();
} //----- Fin de Open

void DotFileWriter::Write ()
// Algorithme : Génère le fichier DOT en listant tous les noeuds d'abord, suivis
// de tous les liens.
{
    Logger::Debug("Appel à DotFileWriter::Write");
    dotFile << HEADER;
    for (unsigned int i = 0; i < numNodes; i++)
    {
        dotFile << "node" << i << " [label=\"" << nodes[i] << "\"];\n";
    }
    for (Link & link : links)
    {
        dotFile << "node" << link.sourceNodeId << " -> node" <<
                link.destinationNodeId << " [label=\"" << link.label <<
                "\"];\n";
    }
    dotFile << FOOTER;
} //----- Fin de Write

//-------------------------------------------------- Constructeurs - destructeur
DotFileWriter::DotFileWriter () : nodes(nullptr), numNodes(0)
{
    Logger::Debug("Appel au constructeur de DotFileWriter");
} //----- Fin du constructeur

DotFileWriter::~DotFileWriter ()
{
    Logger::Debug("Appel au destructeur de DotFileWriter");
    if (nodes != nullptr)
    {
        delete[] nodes;
    }
    Close();
} //----- Fin du destructeur
