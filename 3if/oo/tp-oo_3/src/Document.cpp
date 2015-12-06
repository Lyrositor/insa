#include "Document.h"

void Document::AddLocalHit ()
{
    localHits++;
}

void Document::AddRemoteHit (unsigned long documentId)
{
    if (!remoteHits.count(documentId))
    {
        remoteHits[documentId] = 0;
    }
    remoteHits[documentId]++;
}

unsigned int Document::GetLocalHits () const
{
    return localHits;
}

const std::unordered_map<unsigned long, unsigned int> & Document::GetRemoteHits
        () const
{
    return remoteHits;
}

const std::string & Document::GetUri () const
{
    return uri;
}

bool Document::operator> (const Document & otherDoc) const
{
    return localHits > otherDoc.localHits;
}

Document::Document (const std::string & documentUri) :
        localHits(0), uri(documentUri)
{

}

Document::~Document()
{
}
