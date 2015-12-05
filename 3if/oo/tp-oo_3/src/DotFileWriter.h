#ifndef DOT_FILE_WRITER_H
#define DOT_FILE_WRITER_H

#include <fstream>
#include <string>

class DotFileWriter {
public:

    void Close ();
    bool Open (std::string filename);

    DotFileWriter ();
    virtual ~DotFileWriter ();
protected:
    std::ofstream logFile;
};

#endif // DOT_FILE_WRITER_H
