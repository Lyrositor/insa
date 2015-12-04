#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <map>
#include <unordered_set>

#include "Document.h"

class DotFileWriter;
class LogReader;

class HistoryManager {
public:
    bool fromFile (
            LogReader * logFile,
            std::unordered_set<std::string> excludedExtensions,
            unsigned int startHour,
            unsigned int endHour
    );
    void listDocuments (unsigned int max);
    bool toDotFile (DotFileWriter * dotFile);

    HistoryManager ();
    virtual ~HistoryManager ();

protected:
    std::map<std::string, Document> documents;
};

#endif // HISTORY_MANAGER_H
