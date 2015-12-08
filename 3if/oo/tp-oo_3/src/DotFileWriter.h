/*******************************************************************************
                      DotFileWriter - Écrivain de DOT-file
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <DotFileWriter> (fichier DotFileWriter.h)
#if ! defined ( DOT_FILE_WRITER_H )
#define DOT_FILE_WRITER_H

//--------------------------------------------------------- Interfaces utilisées
#include <forward_list>
#include <fstream>
#include <string>

//------------------------------------------------------------------------ Types
struct Link
{
    unsigned long sourceNodeId;
    unsigned long destinationNodeId;
    std::string label;
};

//------------------------------------------------------------------------------
// Rôle de la classe <DotFileWriter>
//
//------------------------------------------------------------------------------

class DotFileWriter
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    void AddLink (
            unsigned long sourceId, unsigned long targetId,
            const std::string & linkLabel
    );
    // Mode d'emploi :

    void AddNode (unsigned long id, const std::string & label);
    // Mode d'emploi :

    void Close ();
    // Mode d'emploi :

    void InitGraph(unsigned long graphNodes);
    // Mode d'emploi :

    bool Open (const std::string & filename);
    // Mode d'emploi :

    void Write ();
    // Mode d'emploi :

//------------------------------------------------------- Surcharge d'opérateurs
    DotFileWriter & operator = (const DotFileWriter & writer) = delete;
    // Mode d'emploi :

//-------------------------------------------------- Constructeurs - destructeur
    DotFileWriter ();
    // Mode d'emploi :

    DotFileWriter (const DotFileWriter & writer) = delete;
    // Mode d'emploi :

    virtual ~DotFileWriter ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    void writeEscaped (const std::string & s);

protected:
//----------------------------------------------------------- Attributs protégés
    std::ofstream dotFile;
    std::forward_list<Link> links;
    std::string * nodes;
    unsigned long numNodes;

    static const std::string HEADER;
    static const std::string FOOTER;
};

#endif // DOT_FILE_WRITER_H
