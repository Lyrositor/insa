#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <map>
#include <unordered_set>

class Document;
class DotFileWriter;
class LogEntry;
class LogReader;

class HistoryManager {
public:
    bool FromFile (
            LogReader * logFile,
            std::unordered_set<std::string> excludedExtensions,
            unsigned int startHour,
            unsigned int endHour
    );
    void ListDocuments (unsigned int max) const;
    bool ToDotFile (DotFileWriter * dotFile) const;

    HistoryManager (const std::string & serverUrl);
    virtual ~HistoryManager ();

protected:
    std::map<std::string, Document *> documents;
    std::string localServerUrl;

    void addEntry(const LogEntry & entry);
};

#endif // HISTORY_MANAGER_H
