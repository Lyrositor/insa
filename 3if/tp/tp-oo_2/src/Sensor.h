#ifndef SENSOR_H
#define SENSOR_H

#include "EventLink.h"

class Event;
template <typename E> class SegmentedTable;

/**
 * Represents a city's sensor, storing links to events which it has generated.
 *
 * The sensor does not store the events themselves, which must be stored
 * elsewhere; it simply maintains a table of links pointing to those events.
 * This provides a way to look up events by sensor ID instead of by day.
 */
class Sensor {
public:
    Sensor(
            unsigned int sensorId, unsigned int segmentSize,
            unsigned int maxSegments);
    virtual ~Sensor();

    void addEventLink(EventLink el);
    Event getEvent(unsigned int i, SegmentedTable<Event>* const events[]) const;
    EventLink getEventLink(unsigned int i) const;
    unsigned int getId() const;
    unsigned int getNumEvents() const;

protected:
    unsigned int id;
    SegmentedTable<EventLink>* eventLinks;
};


#endif // SENSOR_H
