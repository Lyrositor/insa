#include <functional>
#include <sstream>

#include "Document.h"
#include "DotFileWriter.h"
#include "HistoryManager.h"
#include "LogEntry.h"
#include "Logger.h"
#include "LogReader.h"

const std::unordered_set<std::string> VALID_REQUEST_METHODS = {"GET", "POST"};

bool HistoryManager::FromFile (
        LogReader * logFile,
        const std::unordered_set<std::string> & excludedExtensions,
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
            !excludedExtensions.count(entry.GetRequestUriExtension()) &&
            VALID_REQUEST_METHODS.count(entry.GetRequestMethod()))
        {
            addEntry(entry);
        }
    }
    return true;
}

void HistoryManager::ListDocuments (unsigned int max) const
{
    Documents sortedDocuments = documents;
    std::sort(sortedDocuments.begin(), sortedDocuments.end(), std::greater<Document>());
    for (Documents::size_type i=0, e=sortedDocuments.size(); i!=e && i<max; ++i)
    {
        std::cout << sortedDocuments[i].GetUri() << " (" <<
                sortedDocuments[i].GetLocalHits() << " hits)\n";
    }
    std::cout << std::flush;
}

void HistoryManager::ToDotFile (DotFileWriter * dotFile) const
{
    dotFile->InitGraph(documents.size());
    for (Documents::size_type i = 0, e = documents.size(); i < e; ++i)
    {
        dotFile->AddNode(i, documents[i].GetUri());
        for (auto const & hit : documents[i].GetRemoteHits())
        {
            std::ostringstream ss;
            ss << hit.second;
            dotFile->AddLink(i, hit.first, ss.str());
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
}

void HistoryManager::addEntry (const LogEntry & entry)
{
    // Incrémenter le nombre d'accès au document demandé.
    std::string requestUri = entry.GetRequestUriConverted();
    Documents::size_type requestIndex;
    auto it = documentsByName.find(requestUri);
    if (it == documentsByName.end())
    {
        requestIndex = documents.size();
        documents.emplace_back(requestUri);
        documentsByName[documents[requestIndex].GetUri()] = requestIndex;
    }
    else
    {
        requestIndex = it->second;
    }
    documents[requestIndex].AddLocalHit();

    // Incrémenter le nombre d'accès à ce document au document référent.
    std::string refererUri = entry.GetRefererUrlConverted(localServerUrl);
    Documents::size_type refererIndex;
    it = documentsByName.find(refererUri);
    if (it == documentsByName.end())
    {
        refererIndex = documents.size();
        documents.emplace_back(refererUri);
        documentsByName[documents[refererIndex].GetUri()] = refererIndex;
    }
    else
    {
        refererIndex = it->second;
    }
    documents[refererIndex].AddRemoteHit(requestIndex);
}
