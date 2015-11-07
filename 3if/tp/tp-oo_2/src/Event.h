#ifndef EVENT_H
#define EVENT_H

/** Represents a sensor's events.
 *
 * An event is comprised of the state of traffic at that time and the timestamp
 * in minutes of the time it occurred at.
 */
class Event {
public:
    Event();
    Event(
            unsigned short trafficState, unsigned short month, unsigned short day,
            unsigned short hour, unsigned short minute);

    unsigned short state() const;
    unsigned int date() const;
    unsigned int date(
            unsigned short& month, unsigned short& day, unsigned short& hour,
            unsigned short& minute) const;

protected:
    static unsigned int toTimestamp(
            unsigned short month, unsigned short day, unsigned short hour,
            unsigned short minute);

    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
};

#endif // EVENT_H
