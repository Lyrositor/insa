#include <stdexcept>

#include "Document.h"
#include "HistoryManager.h"
#include "LogEntry.h"
#include "Logger.h"
#include "LogReader.h"

bool HistoryManager::FromFile (
        LogReader * logFile,
        std::unordered_set<std::string> excludedExtensions,
        unsigned int startHour,
        unsigned int endHour
)
{
    while (!logFile->eof())
    {
        LogEntry entry;
        try
        {
            logFile->readLine(entry);
        }
        catch (std::runtime_error & e)
        {
            Logger::Warning(e.what());
            continue;
        }
        if (entry.GetHour() >= startHour && entry.GetHour() < endHour &&
            !excludedExtensions.count(entry.GetRequestUriExtension()))
        {
            addEntry(entry);
        }
    }
    return true;
}

void HistoryManager::ListDocuments (unsigned int max) const
{
    auto it = documents.cbegin();
    for (unsigned int i = 0; i < max && it != documents.cend(); i++, it++)
    {
        std::cout << it->first << " (" << it->second->GetLocalHits() <<
        " hits)" << std::endl;
    }
}

bool HistoryManager::ToDotFile (DotFileWriter * dotFile) const
{
    return false;
}

HistoryManager::HistoryManager(const std::string & serverUrl) :
    localServerUrl(serverUrl)
{
}

HistoryManager::~HistoryManager()
{
    for (auto & pair : documents)
    {
        delete pair.second;
    }
}

void HistoryManager::addEntry (const LogEntry & entry)
{
    // Incrémenter le nombre d'accès au document demandé.
    auto it = documents.find(entry.GetRequestUri());
    Document * requestDocument;
    if (it == documents.end())
    {
        requestDocument = new Document();
        documents[entry.GetRequestUri()] = requestDocument;
    }
    else
    {
        requestDocument = it->second;
    }
    requestDocument->AddLocalHit();

    // Incrémenter le nombre d'accès à ce document au document référent.
    it = documents.find(entry.GetRefererUrlConverted(localServerUrl));
    Document * refererDocument;
    if (it == documents.end())
    {
        refererDocument = new Document();
        documents[entry.GetRefererUrlConverted(localServerUrl)] =
            refererDocument;
    }
    else
    {
        refererDocument = it->second;
    }
    refererDocument->AddRemoteHit(entry.GetRequestUri());
}
