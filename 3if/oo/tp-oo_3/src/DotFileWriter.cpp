#include "DotFileWriter.h"

void DotFileWriter::AddLink (
        unsigned long sourceId, unsigned long targetId, const std::string & linkLabel
)
{
    links.push_front({sourceId, targetId, linkLabel});
}

void DotFileWriter::AddNode (unsigned long id, const std::string & label)
{
    nodes[id] = label;
}

void DotFileWriter::Close ()
{
    if (dotFile.is_open())
    {
        dotFile.close();
    }
}

void DotFileWriter::InitGraph (unsigned long graphNodes)
{
    if (nodes != nullptr)
    {
        delete[] nodes;
    }
    numNodes = graphNodes;
    nodes = new std::string[numNodes];
}

bool DotFileWriter::Open (const std::string & filename)
{
    Close();
    dotFile.open(filename);
    return dotFile.is_open();
}

void DotFileWriter::Write ()
{
    dotFile << HEADER;
    for (unsigned int i = 0; i < numNodes; i++)
    {
        dotFile << "node" << i << "[label=\"" << writeEscaped(nodes[i]) <<
                "\"]\n";
    }
    for (Link & link : links)
    {
        dotFile << "node" << link.sourceNodeId << " -> node" <<
                link.destinationNodeId << " [label=\"" <<
                writeEscaped(link.label) << "\"]\n";
    }
    dotFile << FOOTER;
}

DotFileWriter::DotFileWriter () : nodes(nullptr), numNodes(0)
{

}

DotFileWriter::~DotFileWriter ()
{
    if (nodes != nullptr)
    {
        delete[] nodes;
    }
    Close();
}

std::ofstream & DotFileWriter::writeEscaped (const std::string & s)
{
    for (const char & c : s)
    {
        switch (c)
        {
            case '"': // Aucun break car les " et les \ doivent tous deux être
                      // echappés.
            case '\\':
                dotFile << '\\';
            default:
                dotFile << c;
                break;
        }
    }
    return dotFile;
}
