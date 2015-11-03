#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"
#include "Event.h"
#include "EventLink.h"
#include "SegmentedTable.h"

class Sensor {
public:
    Sensor(unsigned int id, unsigned int segmentSize, unsigned int maxSegments);
    virtual ~Sensor();

    void addEventLink(EventLink el);
    Event getEvent(unsigned int i, SegmentedTable<Event>* const events[]) const;
    EventLink getEventLink(unsigned int i) const;
    unsigned int getId() const;
    const unsigned int getNumEvents() const;

protected:
    unsigned int id;
    SegmentedTable<EventLink>* eventLinks;
};


#endif // SENSOR_H
