#include "Event.h"
#include "SegmentedTable.h"
#include "Sensor.h"

Sensor::Sensor(
        unsigned int sensorId, unsigned int segmentSize,
        unsigned int maxSegments) : id(sensorId) {
    eventLinks = new SegmentedTable<EventLink>(segmentSize, maxSegments);
}

Sensor::~Sensor() {
    delete eventLinks;
}

void Sensor::addEventLink(EventLink el) {
    eventLinks->append(el);
}

Event Sensor::getEvent(
        unsigned int i, SegmentedTable<Event>* const events[]) const {
    EventLink el = getEventLink(i);
    return events[el.day7()]->get(el.index());
}

EventLink Sensor::getEventLink(unsigned int i) const {
    return eventLinks->get(i);
}

unsigned int Sensor::getId() const {
    return id;
}

unsigned int Sensor::getNumEvents() const {
    return eventLinks->length();
}