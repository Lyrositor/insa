#ifndef LOG_READER_H
#define LOG_READER_H

#include <fstream>
#include <string>


class LogEntry;


class LogReader {
public:
    void Close ();
    bool Eof ();
    bool Open (std::string filename);
    void ReadLine (LogEntry & entry);

    LogReader ();
    virtual ~LogReader ();

protected:
    std::ifstream logFile;
    int currentLine;
};


#endif // LOG_READER_H
