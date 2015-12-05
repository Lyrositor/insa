#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <unordered_map>

class Document {
public:
    void AddLocalHit ();
    void AddRemoteHit (const std::string & documentUri);
    unsigned int GetLocalHits () const;
    unsigned int GetRemoteHits (const std::string & documentUri) const;

    Document();
    virtual ~Document();

protected:
    unsigned int localHits;
    std::unordered_map<std::string, unsigned int> remoteHits;
};

#endif // DOCUMENT_H
