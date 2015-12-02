#ifndef LOG_READER_H
#define LOG_READER_H

#include <fstream>
#include <string>

typedef struct LogEntry LogEntry;
struct LogEntry {

};

class LogReader {
public:
    void close ();
    bool open (std::string fileName);
    LogEntry readLine ();

    LogReader ();
    virtual ~LogReader ();

protected:
    std::ifstream logFile;
};

#endif // LOG_READER_H
