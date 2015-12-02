#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <unordered_map>

class Document {
public:
    void addLocalHit();
    void addRemoteHit(std::string);

    Document();
    virtual ~Document();

protected:
    std::string type;
    int localHits;
    std::unordered_map<std::string, int> remoteHits;
};

#endif // DOCUMENT_H
