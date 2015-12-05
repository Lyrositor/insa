#include <limits>
#include <stdexcept>
#include <sstream>

#include "LogEntry.h"
#include "LogReader.h"

const char * ERROR_PARSE_LINE = "Failed to parse line ";

void LogReader::close ()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

bool LogReader::eof ()
{
    return logFile.eof();
}

bool LogReader::open (std::string filename)
{
    currentLine = 0;
    logFile.open(filename);
    return logFile.is_open();
}

void LogReader::readLine (LogEntry & entry)
{
    currentLine++;
    try
    {
        logFile >> entry;
    }
    catch (std::runtime_error & e)
    {
        logFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

}
