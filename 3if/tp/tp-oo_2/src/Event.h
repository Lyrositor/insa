#ifndef EVENT_H
#define EVENT_H

/** Represents a sensor's events.
 *
 * An event is comprised of the state of traffic at that time and the timestamp
 * in minutes of the time it occurred at.
 */
class Event {
public:
    /**
     * Initializes an event generated at t=0 and with the V state.
     */
    Event();

    /**
     * Initializes an event at the specified time with the specified state.
     *
     * @param trafficState the event's state of traffic
     * @param month the event's month (from 0 to 4)
     * @param day the event's day of the month (from 1 to 30/31)
     * @param hour the event's hour (from 0 to 23)
     * @param minute the event's minute (from 0 to 59)
     */
    Event(
            unsigned short trafficState, unsigned short month,
            unsigned short day, unsigned short hour, unsigned short minute);

    /**
     * Returns the event's traffic state.
     *
     * @return the event's traffic state
     */
    unsigned short state() const;

    /**
     * Returns the event's timestamp.
     *
     * @return the event's date's associated timestamp
     */
    unsigned int date() const;

    /**
     * Returns the event's timestamp and provides the date in standard terms.
     *
     * The timestamp is the return value, while the parameters are passed by
     * reference and come out filled with the corresponding values. Use this to
     * quickly get the month, day, hour and minute of an event.
     * @param month the reference used to store the event's month
     * @param day the reference used to store the event's day
     * @param hour the reference used to store the event's hour
     * @param minute the reference used to store the event's minute
     * @return the event's date's associated timestamp
     */
    unsigned int date(
            unsigned short& month, unsigned short& day, unsigned short& hour,
            unsigned short& minute) const;

protected:
    /**
     * Converts a date in standard terms to an internal timestamp.
     *
     * @param month a month (from 0 to 4)
     * @param day a day of the month (from 1 to 30/31)
     * @param hour an hour of the day (from 0 to 23)
     * @param minute a minute of the hour (from 0 to 59)
     */
    static unsigned int toTimestamp(
            unsigned short month, unsigned short day, unsigned short hour,
            unsigned short minute);

    /**
     * The highest order byte (stores the state and part of the timestamp).
     */
    unsigned char byte1;

    /**
     * The second-highest order byte (stores part of the timestamp).
     */
    unsigned char byte2;

    /**
     * The third-highest order byte (stores part of the timestamp).
     */
    unsigned char byte3;
};

#endif // EVENT_H
