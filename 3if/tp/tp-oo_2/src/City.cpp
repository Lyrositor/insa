#include <iostream>

#include "City.h"
#include "Event.h"
#include "EventLink.h"
#include "HashTable.h"
#include "SegmentedTable.h"
#include "Sensor.h"

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
    Event e(state, month, day, hour, minute);
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
    for (unsigned short d = 0; d < 4; d++) {
        short p = static_cast<short>(static_cast<float> (stats[d])/n*100);
        std::cout << STATES[d] << ' ' << p << '%' << std::endl;
    }
}

/*
 * Displays how much time was spent in a traffic jam, per hour and per week day.
 *
 * For every event in the day of the week, get its state: if the state is R or
 * N, it is considered a traffic jam, and the number of traffic jams for that
 * hour of the day is incremented. Then, display the number of traffic jams
 * for every hour relative to the total number of events for that hour.
 */
void City::displayDayTrafficJamStats(unsigned short day7) const {
    SegmentedTable<Event>* dayEvents = events[day7];
    unsigned int stats[24], totals[24];
    for (unsigned int i = 0; i < 24; i++) {
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
    for (unsigned short d = 0; d < 24; d++) {
        short p = 0;
        if (totals[d] > 0)
            p = static_cast<short>(static_cast<float>(stats[d])/totals[d]*100);
        std::cout << day7 + 1 << ' ' << d << ' ' << p << '%' << std::endl;
    }
}

/*
 * Displays the traffic state stats for a day of the week.
 *
 * For every event of the day, get its state, count them, then display how
 * frequently each appeared.
 */
void City::displayDayStateStats(unsigned short day7) const {
    SegmentedTable<Event>* dayEvents = events[day7];
    unsigned int stats[] = {0, 0, 0, 0};

    unsigned int n = dayEvents->length();
    for (unsigned int i = 0; i < n; i++) {
        Event e = dayEvents->get(i);
        stats[e.state()]++;
    }

    // Display the relative stats.
    for (unsigned short d = 0; d < 4; d++) {
        short p = 0;
        if (n > 0)
            p = static_cast<short>(static_cast<float>(stats[d])/n*100);
        std::cout << STATES[d] << ' ' << p << '%' << std::endl;
    }
}

/*
 * Displays the optimal time to leave on a certain journey.
 *
 * The first step is to calculate the "average" day of the week, which keeps
 * only events from the desired sensors and the desired time frame. Then, using
 * that average day, a second loop iterates over every minute of the time frame
 * to find the time which will guarantee the best journey time (based on the
 * state of traffic on each segment at that time).
 */
void City::displayOptimalDepartureTime(
        unsigned short day7, unsigned short hStart, unsigned short hEnd,
        unsigned int segCount, unsigned int segments[]) const {
    // Don't calculate anything if there are no segments.
    if (segCount == 0)
        return;

    // Allocate enough space to store state counts for every sensor, every
    // minute from hStart to 23:59.
    unsigned short maxMinutes = static_cast<unsigned short>(24*60 - hStart*60);
    unsigned int*** averageDay = new unsigned int**[segCount];
    for (unsigned int a_i = 0; a_i < segCount; a_i++) {
        averageDay[a_i] = new unsigned int*[maxMinutes];
        for (unsigned int a_j = 0; a_j < maxMinutes; a_j++) {
            averageDay[a_i][a_j] = new unsigned int[4];
            for (unsigned int a_k = 0; a_k < 4; a_k++)
                averageDay[a_i][a_j][a_k] = 0;
        }
    }

    // Generate the average day.
    for (unsigned int i = 0; i < segCount; i++) {
        // Get the sensor corresponding to the current segment.
        Sensor* sensor = getSensor(segments[i]);
        if (sensor == NULL) {
            for (unsigned int a_i = 0; a_i < segCount; a_i++) {
                for (unsigned int a_j = 0; a_j < maxMinutes; a_j++)
                    delete[] averageDay[a_i][a_j];
                delete[] averageDay[a_i];
            }
            delete[] averageDay;
            return;
        }

        // Initialize every minute of this sensor's average day to {0, 0, 0, 0},
        // since by default no states have been counted.
        for (unsigned int j = 0; j < maxMinutes; j++)
            for (unsigned short h = 0; h < 4; h++)
                averageDay[i][j][h] = 0;

        // Tally the states for this sensor and this time.
        // To calculate the average later, we first need to count every
        // occurrence of a state on a specified sensor at a specified time of
        // the day.
        for (unsigned int k = 0; k < sensor->getNumEvents(); k++) {
            // Get the event link to check the event's day of the week.
            // Only keep events from the specified day of the week.
            EventLink el = sensor->getEventLink(k);
            if (el.day7() != day7)
                continue;

            // Get the event to check its date.
            // Only keep events between hStart and 23:59. Don't stop at hEnd
            // since only the departure time is constrained between hStart and
            // hEnd, and the journey can go on beyond hEnd (but not beyond the
            // day's end into the next day).
            Event e = sensor->getEvent(k, events);
            unsigned short month, day, hour, minutes;
            e.date(month, day, hour, minutes);
            if (hour < hStart)
                continue;

            // Increment the state count for this state at the current time.
            int numMinutes = (hour-hStart)*60 + minutes;
            averageDay[i][numMinutes][e.state()]++;
        }
    }

    // Calculate the best times for the generated average day.
    // By default, no valid journey has been found.
    unsigned short bestJourneyTime = 0, bestDepartureTime = 0;
    bool noValidJourney = true;
    for (int j = 0; j < (hEnd - hStart)*60; j++) {
        // By default, assume the journey is valid.
        unsigned short journeyTime = 0;
        bool invalidJourney = false;

        // For every segment, get its state at the current time, which gets
        // incremented at each segment, in accordance with the state's value.
        for (unsigned int i = 0; i < segCount; i++) {
            // Assume the current state is V initially, with no counts.
            unsigned short state = 0;
            unsigned int stateCount = 0;

            // Loop over every state to find the one with the highest count.
            // If there is an equality (e.g. 2 J and 2 R), the better state is
            // picked (e.g. J would be picked instead of R or N).
            for (unsigned short h = 0; h < 4; h++)
                if (averageDay[i][j + journeyTime][h] > stateCount) {
                    state = h;
                    stateCount = averageDay[i][j + journeyTime][h];
                }

            // If no states were counted, this means there are no data points
            // for this time of the day, and the journey is not valid as a
            // result.
            if (stateCount == 0) {
                invalidJourney = true;
                break;
            }

            // Increment the journey time by 1 if the state was V, 2 if the
            // state was J, 4 if the state was R and 10 if the state was N.
            journeyTime += STATE_TIMES[state];

            // Unless this is the very first valid journey, if the journey time
            // is already higher than the best journey time consider this an
            // invalid journey and skip it.
            if (journeyTime >= bestJourneyTime && !noValidJourney) {
                invalidJourney = true;
                break;
            }
        }

        // If the journey was invalid, continue on to the next minute and try
        // to calculate another journey again.
        if (invalidJourney)
            continue;

        // If we have reached this point, that means this journey is the best
        // one we have calculated yet, so save it.
        noValidJourney = false;
        bestJourneyTime = journeyTime;
        bestDepartureTime = j;

        // If the time is the number of segments, this means this is the best
        // possible time, since that means that for every segment the state was
        // V (segCount * 1 = segCount).
        if (bestDepartureTime == segCount)
            break;
    }

    // Display the optimal departure time if a valid journey was found.
    if (!noValidJourney) {
        int bestMinute = bestDepartureTime % 60;
        int bestHour = (bestDepartureTime - bestMinute) / 60;
        std::cout << day7 + 1 << ' ' << hStart + bestHour << ' ' <<
                bestMinute << ' ' << bestJourneyTime << std::endl;
    }

    // Delete the average day.
    for (unsigned int a_i = 0; a_i < segCount; a_i++) {
        for (unsigned int a_j = 0; a_j < maxMinutes; a_j++)
            delete[] averageDay[a_i][a_j];
        delete[] averageDay[a_i];
    }
    delete[] averageDay;
}

/*
 * Adds a new sensor to the array of sensors and returns its new index.
 */
unsigned short City::addSensor(unsigned int sensorId) {
    sensors[numSensors] = new Sensor(
            sensorId, EVENT_LINK_SEGMENT_SIZE, MAX_SENSORS);
    numSensors++;
    return static_cast<unsigned short>(numSensors - 1);
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