#include "Document.h"

void Document::AddLocalHit ()
{
    localHits++;
}

void Document::AddRemoteHit (const std::string & documentUri)
{
    if (!remoteHits.count(documentUri))
    {
        remoteHits[documentUri] = 0;
    }
    remoteHits[documentUri]++;
}

unsigned int Document::GetLocalHits () const
{
    return localHits;
}

unsigned int Document::GetRemoteHits (const std::string & documentUri) const
{
    return remoteHits.at(documentUri);
}

Document::Document() : localHits(0)
{
}

Document::~Document()
{
}
