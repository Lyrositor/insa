#include <stdexcept>
#include <sstream>

#include "LogEntry.h"
#include "LogReader.h"

const char * ERROR_PARSE_LINE = "Failed to parse line ";

void LogReader::Close ()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

bool LogReader::Eof ()
{
    return logFile.eof();
}

bool LogReader::Open (std::string filename)
{
    Close();
    currentLine = 0;
    logFile.open(filename);
    return logFile.is_open();
}

void LogReader::ReadLine (LogEntry & entry)
{
    currentLine++;
    try
    {
        logFile >> entry;
    }
    catch (std::runtime_error & e)
    {
        std::stringstream ss;
        ss << ERROR_PARSE_LINE << currentLine << " (" << e.what() << ")";
        throw std::runtime_error(ss.str());
    }
}

LogReader::LogReader () : currentLine(0)
{

}

LogReader::~LogReader ()
{
    Close();
}
