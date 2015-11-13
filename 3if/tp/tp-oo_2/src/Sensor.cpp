#include "Event.h"
#include "SegmentedTable.h"
#include "Sensor.h"

/*
 * Initializes an empty table of links.
 */
Sensor::Sensor(
        unsigned int sensorId, unsigned int segmentSize,
        unsigned int maxSegments) : id(sensorId) {
    eventLinks = new SegmentedTable<EventLink>(segmentSize, maxSegments);
}

/*
 * Deletes all the links to the sensor's events.
 */
Sensor::~Sensor() {
    delete eventLinks;
}

/*
 * Appends a link to an event to the table of linked events.
 */
void Sensor::addEventLink(EventLink el) {
    eventLinks->append(el);
}

/*
 * Fetches a link to an event, follows that link and returns the found event.
 */
Event Sensor::getEvent(
        unsigned int i, SegmentedTable<Event>* const events[]) const {
    EventLink el = getEventLink(i);
    return events[el.day7()]->get(el.index());
}

/*
 * Looks up the link at the specified index in table of links.
 */
EventLink Sensor::getEventLink(unsigned int i) const {
    return eventLinks->get(i);
}

/*
 * Returns the stored ID.
 */
unsigned int Sensor::getId() const {
    return id;
}

/*
 * The number of events is equal to the number of linked events, so the method
 * merely counts the size of the links table.
 */
unsigned int Sensor::getNumEvents() const {
    return eventLinks->length();
}