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
    unsigned long sourceNodeId;  // L'ID du noeud de source du lien.
    unsigned long destinationNodeId;  // L'ID du noeud de destination du lien.
    std::string label;  // L'étiquette à afficher à côté du lien.
};

//------------------------------------------------------------------------------
// Rôle de la classe <DotFileWriter>
// Transcrit un graphe au format Graphviz et permet de l'écrire dans un fichier
// DOT.
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
    // <sourceId> : l'ID du noeud de source du lien
    // <targetId> : l'ID du noeud de destination du lien
    // <linkLabel> : l'étiquette à afficher à côté du lien
    // Mode d'emploi : Ajoute un lien entre le noeud <sourceId> et le noeud
    // <targetId>, avec une étiquette <linkLabel> à côté.
    // Contrat : <sourceId> et <targetId> devraient déjà avoir été ajoutés grâce
    // à <AddNode>. Le graphe doit être initialisé avec InitGraph au préalable.

    void AddNode (unsigned long id, const std::string & label);
    // <id> : l'ID identifiant le noeud
    // <label> : l'étiquette à afficher à côté du noeud
    // Mode d'emploi : Ajoute un nouveau noeud du graphe, identifié par son
    // <id>. Son <label> est affiché à côté du noeud dans le graphe généré.
    // Contrat : Le graphe doit être initialisé avec InitGraph au préalable.

    void Close ();
    // Mode d'emploi : Ferme le flux de fichier associé, s'il a été ouvert. Si
    // aucun flux n'a été ouvert, aucune action n'est effectuée.

    void InitGraph(unsigned long graphNodes);
    // <graphNodes> : le nombre de noeuds dans le graphe
    // Mode d'emploi : Initialise le graphe associé, allouant assez de mémoire
    // pour stocker un nombre <graphNodes> de noeuds. Doit être appelé avant de
    // commencer à construire les noeuds et les liens. Si un graphe avait déjà
    // été initialisé, l'ancien graphe est supprimé et un nouveau est créé.

    bool Open (const std::string & filename);
    // <filename> : le nom de fichier à ouvrir en mode écriture
    // Mode d'emploi : Ouvre un fichier <filename> en mode écriture. Le fichier
    // devrait avoir une extension ".dot", mais ceci n'est pas obligatoire.

    void Write ();
    // Mode d'emploi : Écrit le fichier DOT associé au graphe initialisé par
    // InitGraph.
    // Contrat : Le graphe doit être initialisé avec InitGraph au préalable.

//------------------------------------------------------- Surcharge d'opérateurs
    DotFileWriter & operator = (const DotFileWriter & writer) = delete;
    // <writer> : l'écrivain à copier
    // Mode d'emploi : Supprimé. La copie est interdite pour éviter d'avoir des
    // conflits liés aux flux.

//-------------------------------------------------- Constructeurs - destructeur
    DotFileWriter ();
    // Mode d'emploi : Initialise un écrivain de fichier DOT sans graphe
    // associé. Le graphe doit ensuite être initialisé avec InitGraph.

    DotFileWriter (const DotFileWriter & writer) = delete;
    // <writer> : l'écrivain à copier
    // Mode d'emploi : Supprimé. La copie est interdite pour éviter d'avoir des
    // conflits liés aux flux.

    virtual ~DotFileWriter ();
    // Mode d'emploi : Supprime l'écrivain, ferme tout flux de fichier associé
    // et supprime le graphe s'il a été initialisé.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs protégés
    std::ofstream dotFile;  // Le flux de fichier de sortie associé
    std::forward_list<Link> links;  // La liste de liens de graphe
    std::string * nodes;  // Le tableau de noeuds de graphe
    unsigned long numNodes;  // Le nombre de noeuds de graphe

    static const std::string HEADER;  // L'en-tête du fichier DOT à écrire
    static const std::string FOOTER;  // Le pied de page du fichier DOT à écrire
};

#endif // DOT_FILE_WRITER_H
