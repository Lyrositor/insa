#ifndef DOT_FILE_WRITER_H
#define DOT_FILE_WRITER_H

#include <fstream>
#include <string>

class DotFileWriter {
public:
    void close ();
    bool open (std::string filename);

    DotFileWriter ();
    virtual ~DotFileWriter ();
protected:
    std::ofstream logFile;
};

#endif // DOT_FILE_WRITER_H
