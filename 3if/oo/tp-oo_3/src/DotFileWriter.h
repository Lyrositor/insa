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

//------------------------------------------------------------------- Constantes

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

//-------------------------------------------------- Constructeurs - destructeur
    DotFileWriter ();
    // Mode d'emploi :

    virtual ~DotFileWriter ();
    // Mode d'emploi :

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    void writeEscaped (const std::string & s);

private:
//------------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------------- Attributs protégés
    static const std::string HEADER;
    static const std::string FOOTER;

    std::ofstream dotFile;
    std::forward_list<Link> links;
    std::string * nodes;
    unsigned long numNodes;

private:
//------------------------------------------------------------- Attributs privés

//---------------------------------------------------------------- Classes amies

//-------------------------------------------------------------- Classes privées

//----------------------------------------------------------------- Types privés
};

//------------------------------------------ Types dépendants de <DotFileWriter>

#endif // DOT_FILE_WRITER_H
