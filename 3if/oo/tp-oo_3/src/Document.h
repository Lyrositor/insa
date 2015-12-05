#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <unordered_map>

class Document {
public:
    void AddLocalHit ();
    void AddRemoteHit (unsigned long documentId);
    unsigned long GetId () const;
    unsigned int GetLocalHits () const;
    const std::unordered_map<unsigned long, unsigned int> & GetRemoteHits ()
            const;
    const std::string & GetUri() const;

    Document (unsigned long documentId, const std::string & documentUri);
    virtual ~Document ();

protected:
    unsigned long id;
    unsigned int localHits;
    std::unordered_map<unsigned long, unsigned int> remoteHits;
    std::string uri;
};

#endif // DOCUMENT_H
