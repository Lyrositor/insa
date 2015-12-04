#include "LogEntry.h"
#include "LogReader.h"

void LogReader::close ()
{

}

bool LogReader::eof ()
{
    return logFile.eof();
}

bool LogReader::open (std::string filename)
{
    logFile.open(filename);
    return logFile.is_open();
}

LogEntry LogReader::readLine ()
{
    LogEntry entry;
    logFile >> entry;
    return entry;
}

LogReader::LogReader ()
{

}

LogReader::~LogReader ()
{

}
