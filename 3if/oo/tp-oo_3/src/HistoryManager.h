#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Document;
class DotFileWriter;
class LogEntry;
class LogReader;

typedef std::vector<Document> Documents;

class HistoryManager
{
public:
    bool FromFile (
            LogReader * logFile,
            const std::unordered_set<std::string> & excludedExtensions,
            unsigned int startHour,
            unsigned int endHour
    );
    void ListDocuments (unsigned int max) const;
    void ToDotFile (DotFileWriter * dotFile) const;

    HistoryManager (const std::string & serverUrl);
    virtual ~HistoryManager ();

protected:
    Documents documents;
    std::unordered_map<std::string, Documents::size_type> documentsByName;
    const std::string localServerUrl;

    void addEntry(const LogEntry & entry);
};

#endif // HISTORY_MANAGER_H
