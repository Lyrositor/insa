#include <iostream>

#include "City.h"

/*
 * Initializes the city to a default state.
 *
 * By default, there are no sensors and seven days with no events; therefore,
 * seven empty event tables are initialized. An empty hash table is also
 * created, since no sensors are known yet.
 */
City::City() : numSensors(0) {
    for (unsigned short i = 0; i < NUM_DAYS; i++)
        events[i] = new SegmentedTable<Event>(EVENT_SEGMENT_SIZE, MAX_EVENTS);
    sensorIndices = new HashTable(MAX_SENSORS*10, MAX_SENSORS);
}

/*
 * Destructs the city.
 *
 * Deletes every initialized event table, sensor and the hash table of indices.
 */
City::~City() {
    for (unsigned short i = 0; i < NUM_DAYS; i++)
        delete events[i];
    for (unsigned short i = 0; i < numSensors; i++)
        delete sensors[i];
    delete sensorIndices;
}

/*
 * Adds a new sensor event to the list of registered events.
 *
 * This method first tries to find a sensor with a matching ID; if not found,
 * it will create it. Once it has the corresponding sensor's index, it creates
 * the event and a link to it. The event itself is stored in the table of days
 * of the week, while the link is stored in the table of sensors.
 * Example: an event for sensor 42 which took place on Wednesday is first added
 * to events[2], then a link to that event is added to the sensor with ID 42.
 */
void City::addEvent(unsigned int sensorId, unsigned short state,
                    unsigned short month, unsigned short day,
                    unsigned short hour, unsigned short minute,
                    unsigned short day7) {
    // Get the index of the sensor associated with the event.
    // If a sensor with that ID has not yet been created, create it and add it
    // to the array (also adds its new index to the hash table).
    unsigned short sensorIndex = numSensors;
    unsigned short numIndices = sensorIndices->entries(sensorId);
    for (unsigned short i = 0; i < numIndices; i++) {
        unsigned short j = sensorIndices->get(sensorId, i);
        if (sensors[j]->getId() == sensorId) {
            sensorIndex = j;
            break;
        }
    }
    if (sensorIndex == numSensors) {
        sensorIndex = addSensor(sensorId);
        sensorIndices->add(sensorId, sensorIndex);
    }

    // Create the event and the link to it.
    Event e(sensorIndex, state, month, day, hour, minute);
    unsigned int index = events[day7]->append(e);
    EventLink el(day7, index);
    sensors[sensorIndex]->addEventLink(el);
}

/*
 * Displays the traffic state stats for a specific sensor.
 *
 * Finds the sensor with a matching ID, looks up all its linked events to find
 * all the changes of states, counts them, then displays how frequently each
 * appeared.
 */
void City::displaySensorStateStats(unsigned int sensorId) const {
    // Try to locate the sensor.
    Sensor* sensor = getSensor(sensorId);
    if (sensor == NULL)
        return;

    // Count every occurrence of a stat.
    unsigned int stats[4] = {0, 0, 0, 0};
    const unsigned int n = sensor->getNumEvents();
    for (unsigned int j = 0; j < n; j++) {
        Event e = sensor->getEvent(j, events);
        stats[e.state()]++;
    }

    // Display the relative stats.
    for (unsigned short d = 0; d < 4; d++)
        std::cout << STATES[d] << ' ' <<
                round((float) (stats[d]) / (float) (n) * 100) << '%' <<
                std::endl;
}

/*
 * Displays how much time was spent in a traffic jam, per hour and per week day.
 */
void City::displayDayTrafficJamStats(unsigned short day7) const {
    SegmentedTable<Event>* dayEvents = events[day7];
    unsigned int stats[24], totals[24];
    for (unsigned int i = 0; i < 23; i++) {
        stats[i] = 0;
        totals[i] = 0;
    }

    // Count every occurrence of a stat.
    unsigned int n = dayEvents->length();
    unsigned short month, day, hour, minute;
    for (unsigned int i = 0; i < n; i++) {
        Event e = dayEvents->get(i);
        e.date(month, day, hour, minute);
        if (e.state() == 2 || e.state() == 3)
            stats[hour]++;
        totals[hour]++;
    }

    // Display the relative stats.
    for (unsigned short d = 0; d < 23; d++)
        std::cout << day7 + 1 << ' ' << d << ' ' <<
                round((float) (stats[d]) / (float) (totals[d]) * 100) << '%' <<
                std::endl;
}

/*
 * Displays the traffic state stats for a day of the week.
 */
void City::displayDayStateStats(unsigned short day7) const {
    SegmentedTable<Event>* dayEvents = events[day7];
    unsigned int stats[] = {0, 0, 0, 0};

    unsigned int n = dayEvents->length();
    for (unsigned int i = 0; i < n; i++) {
        Event e = dayEvents->get(i);
        stats[e.state()]++;
    }

    for (unsigned short d = 0; d < 4; d++)
        std::cout << STATES[d] << ' ' <<
                round((float) (stats[d]) / (float) (n) * 100) << '%' <<
                std::endl;
}

/*
 * Displays the optimal time to leave on a certain journey.
 */
void City::displayOptimalDepartureTime(
        unsigned short day7, unsigned short hStart, unsigned short hEnd,
        unsigned int segCount, unsigned int segments[]) const {
}

/*
 * Adds a new sensor to the array of sensors and returns its new index.
 */
unsigned short City::addSensor(unsigned int sensorId) {
    sensors[numSensors] = new Sensor(
            sensorId, EVENT_LINK_SEGMENT_SIZE, MAX_SENSORS);
    numSensors++;
    return (unsigned short) (numSensors - 1);
}

/*
 * Gets a sensor by its ID.
 *
 * Looks up the ID in the hash table first to narrow down the available choices,
 * then picks the sensor with the matching ID.
 */
Sensor* City::getSensor(unsigned int sensorId) const {
    unsigned short numIndices = sensorIndices->entries(sensorId);
    for (unsigned short i = 0; i < numIndices; i++) {
        Sensor* sensor = sensors[sensorIndices->get(sensorId, i)];
        if (sensor->getId() == sensorId)
            return sensor;
    }
    return NULL;
}

/*
 * Rounds a floating-point number to the nearest integer.
 */
unsigned int round(float n) {
    unsigned int d = (unsigned int) n;
    return (n - d) > 0.5 ? d + 1 : d;
}