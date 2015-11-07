#ifndef SEGMENTEDTABLE_H
#define SEGMENTEDTABLE_H

/**
 * A table which can adjust its size in large chunks and works as an array.
 *
 * The table is made up of multiple segments of a preset size. When a segment
 * runs out of size to store data, a new segment is allocated. Accessing
 * elements works like an array, since the segments are stored in order.
 */
template <typename E> class SegmentedTable {
public:
    SegmentedTable(unsigned int size, unsigned int maxSegments);
    virtual ~SegmentedTable();

    unsigned int append(E element);
    const E get(unsigned int index) const;
    unsigned int length() const;

protected:
    E** segments;
    unsigned short numSegments;
    unsigned int numSegmentEntries;
    unsigned int segmentSize;

    void appendSegment();
};

#endif // SEGMENTEDTABLE_H
