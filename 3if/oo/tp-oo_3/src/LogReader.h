#ifndef LOG_READER_H
#define LOG_READER_H

#include <fstream>
#include <string>


class LogEntry;


class LogReader {
public:
    void close ();
    bool eof ();
    bool open (std::string filename);
    void readLine (LogEntry & entry);

    LogReader ();
    virtual ~LogReader ();

protected:
    std::ifstream logFile;
    int currentLine;
};


#endif // LOG_READER_H
