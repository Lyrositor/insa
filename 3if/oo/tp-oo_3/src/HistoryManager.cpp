#include "HistoryManager.h"
#include "LogEntry.h"
#include "LogReader.h"

bool HistoryManager::fromFile(
        LogReader * logFile,
        std::unordered_set<std::string> excludedExtensions,
        unsigned int startHour,
        unsigned int endHour)
{
    while (!logFile->eof())
    {
        LogEntry entry;
        entry = logFile->readLine();
    }
    return false;
}

void HistoryManager::listDocuments(unsigned int max)
{

}

HistoryManager::HistoryManager()
{

}

HistoryManager::~HistoryManager()
{

}

bool HistoryManager::toDotFile(DotFileWriter * dotFile)
{
    return false;
}
