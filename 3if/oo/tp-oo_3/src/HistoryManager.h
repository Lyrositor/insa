/*******************************************************************************
            HistoryManager - Gère un graphe de parcours d'un serveur
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <HistoryManager> (fichier HistoryManager.h)
#if ! defined ( HISTORY_MANAGER_H )
#define HISTORY_MANAGER_H

//--------------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//------------------------------------------------------------------------ Types
class Document;
class DotFileWriter;
class LogEntry;
class LogReader;

typedef std::vector<Document> Documents;
typedef std::unordered_map<std::string, Documents::size_type> NamedDocuments;

//------------------------------------------------------------------------------
// Rôle de la classe <HistoryManager>
// Gère un graphe d'historique de parcours d'un serveur Apache. Peut traiter les
// fichiers de log d'Apache pour en déduire les documents qui ont été parcourus.
//------------------------------------------------------------------------------

class HistoryManager
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- Méthodes publiques
    bool FromFile (
            LogReader & logFile,
            const std::unordered_set<std::string> & excludedExtensions,
            unsigned int startHour,
            unsigned int endHour
    );
    // <logFile> : un lecteur de fichier Apache ouvert
    // <excludedExtensions> : la liste des extensions à exclure
    // <startHour> : l'heure de début pour la plage horaire (incluse)
    // <endHour> : l'heure de fin pour la plage horaire (exclue)
    // Mode d'emploi : Utilise le lecteur de logs Apache <logFile> pour extraire
    // l'historique de parcours d'un fichier. Seuls les documents avec des
    // extensions qui ne sont pas dans la liste <excludedExtensions> et qui
    // ont été visités dans la plage horaire [startHour; endHour[ sont traités.
    // Contrat : <logFile> doit être ouvert et disponible pour la lecture.

    void ListDocuments (unsigned int max) const;
    // <max> : le nombre maximum de documents à lister
    // Mode d'emploi : Affiche la liste des <max> documents les plus populaires
    // (ceux qui ont été le plus visité). S'il y a moins de documents que max,
    // tous les documents ayant été visités au moins une fois sont listés.

    void ToDotFile (DotFileWriter & dotFile) const;
    // <dotFile> : un écrivain de fichier DOT ouvert
    // Mode d'emploi : Génère un fichier DOT à partir de l'historique stocké. Le
    // fichier généré peut ensuite être passé à Graphviz pour génération d'une
    // image du graphe.
    // Contrat : <dotFile> doit être ouvert et disponible pour l'écriture.

//-------------------------------------------------- Constructeurs - destructeur
    HistoryManager (const std::string & serverUrl);
    // <serverUrl> : l'URL du serveur local associé à cet historique
    // Mode d'emploi : Construit un nouveau gestionnaire d'historique pour le
    // serveur spécifié par <serverUrl>. Si une URL commence par <serverUrl>,
    // le document associé est considéré comme faisant partie du serveur local.

    virtual ~HistoryManager ();
    // Mode d'emploi : Détruit le gestionnaire d'historique.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Méthodes protégées
    void addEntry (const LogEntry & entry);
    // <entry> : L'entrée à ajouter
    // Mode d'emploi : Ajoute une entrée d'un fichier de log à l'historique.
    // Chaque entrée correspond à un ou deux documents, qui sont ajoutés à la
    // liste de documents s'ils n'existent pas déjà ; sinon, leurs compteurs
    // respectifs sont incrémentés.

protected:
//----------------------------------------------------------- Attributs protégés
    Documents documents;  // Le tableau de documents ; leur position correspond
                          // à leur ID
    NamedDocuments documentsByName;  // La liste associant l'URI des documents
                                     // à leur ID, pour faciliter leur recherche
                                     // par URI
    const std::string localServerUrl;  // L'URL du serveur local associé au
                                       // gestionnaire d'historique
};

#endif // HISTORY_MANAGER_H
