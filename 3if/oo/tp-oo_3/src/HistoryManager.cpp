#include <sstream>
#include <stdexcept>

#include "Document.h"
#include "DotFileWriter.h"
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
    while (!logFile->Eof())
    {
        LogEntry entry;
        try
        {
            logFile->ReadLine(entry);
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
    auto it = documentsById.cbegin();
    for (unsigned int i = 0; i < max && it != documentsById.cend(); i++, ++it)
    {
        std::cout << it->second->GetUri() << " (" <<
                it->second->GetLocalHits() << " hits)" << std::endl;
    }
}

void HistoryManager::ToDotFile (DotFileWriter * dotFile) const
{
    dotFile->InitGraph(documentsById.size());
    for (auto const & doc : documentsById)
    {
        dotFile->AddNode(doc.second->GetId(), doc.second->GetUri());
        for (auto const & hit : doc.second->GetRemoteHits())
        {
            std::ostringstream ss;
            ss << hit.second;
            dotFile->AddLink(doc.second->GetId(), hit.first, ss.str());
        }
    }
    dotFile->Write();
}

HistoryManager::HistoryManager(const std::string & serverUrl) :
    localServerUrl(serverUrl)
{
}

HistoryManager::~HistoryManager()
{
    for (auto & pair : documentsById)
    {
        delete pair.second;
    }
}

void HistoryManager::addEntry (const LogEntry & entry)
{
    // Incrémenter le nombre d'accès au document demandé.
    auto it = documentsByName.find(entry.GetRequestUri());
    Document * requestDocument;
    if (it == documentsByName.end())
    {
        requestDocument = new Document(
                documentsById.size(), entry.GetRequestUri()
        );
        documentsById[requestDocument->GetId()] = requestDocument;
        documentsByName[requestDocument->GetUri()] = requestDocument;
    }
    else
    {
        requestDocument = it->second;
    }
    requestDocument->AddLocalHit();

    // Incrémenter le nombre d'accès à ce document au document référent.
    it = documentsByName.find(entry.GetRefererUrlConverted(localServerUrl));
    Document * refererDocument;
    if (it == documentsByName.end())
    {
        refererDocument = new Document(
                documentsById.size(),
                entry.GetRefererUrlConverted(localServerUrl)
        );
        documentsById[refererDocument->GetId()] = refererDocument;
        documentsByName[refererDocument->GetUri()] = refererDocument;
    }
    else
    {
        refererDocument = it->second;
    }
    refererDocument->AddRemoteHit(refererDocument->GetId());
}
