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
    LogEntry readLine ();

    LogReader ();
    virtual ~LogReader ();

protected:
    std::ifstream logFile;
};


#endif // LOG_READER_H
