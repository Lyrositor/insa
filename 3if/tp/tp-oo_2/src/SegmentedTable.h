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
    /**
     * Initializes a segmented table with its segment qualifiers.
     *
     * @param size the size of an individual segment
     * @param maxSegments the maximum number of segments to be allocated
     */
    SegmentedTable(unsigned int size, unsigned int maxSegments);

    /**
     * Destructs the table and all its segments.
     */
    virtual ~SegmentedTable();

    /**
     * Appends a new element to the table's end.
     *
     * @param element the element to append
     * @return the new index of the appended element
     */
    unsigned int append(E element);

    /**
     * Fetches an element from the table by its index.
     *
     * Its index is relative to the very first element in the table, not its
     * position in its individual segment.
     * @param index the index of the element to retrieve
     * @return the fetched element
     */
    const E get(unsigned int index) const;

    /**
     * The length of the table, calculated as the total number of all elements.
     *
     * @return the number of entries in the table
     */
    unsigned int length() const;

protected:
    /**
     * An array of segments, each an array of elements.
     */
    E** segments;

    /**
     * The current number of allocated segments.
     */
    unsigned short numSegments;

    /**
     * The number of entries in the last segment initialized.
     */
    unsigned int numSegmentEntries;

    /**
     * The maximum size of a segment.
     */
    unsigned int segmentSize;

    /**
     * Appends a new segment just after the previous segment.
     *
     * New segments are appended when all previous segments have run out of
     * space for more elements.
     */
    void appendSegment();
};

#endif // SEGMENTEDTABLE_H
