#include "Event.h"
#include "EventLink.h"
#include "SegmentedTable.h"

/*
 * Initializes the list of segments. By default, there are no segments, so the
 * array is empty.
 */
template <typename E>
SegmentedTable<E>::SegmentedTable(
        unsigned int size, unsigned int maxSegments) :
        numSegments(0), numSegmentEntries(0), segmentSize(size) {
    segments = new E*[maxSegments];
}

/*
 * Deletes all the segments and the list of segments.
 */
template <typename E>
SegmentedTable<E>::~SegmentedTable() {
    for (int i = 0; i < numSegments; i++)
        delete[] segments[i];
    delete[] segments;
}

/*
 * If there is no more space in the latest segment, a new segment is allocated
 * first. Then, the event is added to the last segment which still had some free
 * space.
 */
template<typename E>
unsigned int SegmentedTable<E>::append(E element) {
    if (numSegmentEntries >= segmentSize || numSegments == 0)
        appendSegment();
    segments[numSegments - 1][numSegmentEntries] = element;
    numSegmentEntries++;
    return numSegmentEntries - 1;
}

/*
 * First calculates the segment an item is in by calculating how many segments
 * were filled before this index is reached, then calculates the element's
 * position in the chosen segment.
 */
template <typename E>
const E SegmentedTable<E>::get(unsigned int index) const {
    unsigned short segmentIndex = static_cast<unsigned short>(index/segmentSize);
    return segments[segmentIndex][index % segmentSize];
}

/*
 * Allocates memory for a new segment then adds it to the array of segments.
 */
template <typename E>
void SegmentedTable<E>::appendSegment() {
    segments[numSegments] = new E[segmentSize];
    numSegments++;
    numSegmentEntries = 0;
}

/*
 * The length is calculated as the size of all the filled segments plus the
 * number of entries in the last unfilled segment.
 */
template<typename E>
unsigned int SegmentedTable<E>::length() const {
    unsigned int l = 0;
    if (numSegments > 0) {
        l += static_cast<unsigned int>(numSegments - 1) * segmentSize;
        l += numSegmentEntries;
    }
    return l;
}

/* List all possible implementations. */
template class SegmentedTable<Event>;
template class SegmentedTable<EventLink>;