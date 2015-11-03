#ifndef SEGMENTEDTABLE_H
#define SEGMENTEDTABLE_H

#include "Event.h"

template <typename E> class SegmentedTable {
public:
    SegmentedTable(unsigned int segmentSize, unsigned int maxSegments);
    virtual ~SegmentedTable();

    unsigned int append(E element);
    const E get(unsigned int index) const;
    const unsigned int length() const;

protected:
    E** segments;
    unsigned short numSegments;
    unsigned int numSegmentEntries;
    unsigned int segmentSize;

    void appendSegment();
};

#include "SegmentedTable_impl.h"

#endif // SEGMENTEDTABLE_H
