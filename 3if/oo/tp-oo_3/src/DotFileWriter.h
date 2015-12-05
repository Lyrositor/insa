#ifndef DOT_FILE_WRITER_H
#define DOT_FILE_WRITER_H

#include <forward_list>
#include <fstream>
#include <string>

struct Link
{
    unsigned long sourceNodeId;
    unsigned long destinationNodeId;
    std::string label;
};

class DotFileWriter
{
public:
    void AddLink (
            unsigned long sourceId, unsigned long targetId,
            const std::string & linkLabel
    );
    void AddNode (unsigned long id, const std::string & label);
    void Close ();
    void InitGraph(unsigned long graphNodes);
    bool Open (const std::string & filename);
    void Write ();

    DotFileWriter ();
    virtual ~DotFileWriter ();
protected:
    static constexpr char const * HEADER = "digraph {\n";
    static constexpr char const * FOOTER = "}\n";

    std::ofstream dotFile;
    std::forward_list<Link> links;
    std::string * nodes;
    unsigned long numNodes;

    std::ofstream & writeEscaped(const std::string & s);
};

#endif // DOT_FILE_WRITER_H
