#include "config.h"
#include "Event.h"

/*
 * Initializes an empty event.
 */
Event::Event() : byte1(0), byte2(0), byte3(0) {
}

/*
 * Performs some bit-arithmetic to store an event's data into as little space as
 * possible. The state takes up 2 bits while the timestamp takes up 22 bits.
 */
Event::Event(
        unsigned short trafficState, unsigned short month, unsigned short day,
        unsigned short hour, unsigned short minute) {
    // Convert the date to a timestamp.
    unsigned int timestamp = toTimestamp(month, day, hour, minute);

    byte1 = static_cast<unsigned char>((trafficState & 3) << 6);
    byte1 |= ((timestamp >> 16) & 0x3F);
    byte2 = static_cast<unsigned char>((timestamp >> 8) & 0xFF);
    byte3 = static_cast<unsigned char>(timestamp & 0xFF);
}

/*
 * Retrieves an event's state from its 2-bit structure and returns it as a
 * short instead.
 */
unsigned short Event::state() const {
    return static_cast<unsigned short>((byte1 >> 6) & 3);
}

/*
 * Retrieves a timestamp from its 22-bit structure and returns it as an integer
 * instead.
 */
unsigned int Event::date() const {
    return static_cast<unsigned int>(((byte1 & 0x3F) << 16)|(byte2 << 8)|byte3);
}

/*
 * Converts a timestamp back into a date by doing the reverse conversion
 * operation.
 */
unsigned int Event::date(
        unsigned short& month, unsigned short& day, unsigned short& hour,
        unsigned short& minute) const {
    // Extract the minute, the hour and the total amount of days from the
    // timestamp.
    unsigned int timestamp = date();
    minute = static_cast<unsigned short>(timestamp % 60);
    hour = static_cast<unsigned short>(((timestamp - minute)/60) % 24);
    day = static_cast<unsigned short>((timestamp - minute -
            static_cast<unsigned int>(hour*60))/(24 * 60));

    // Calculates the number of months and days by subtracting days from the
    // total amount for every month that fits inside the timestamp. When 30 or
    // 31 days can no longer be removed, the month has been found (and thus the
    // day of the month).
    month = 0;
    for (unsigned int k = 0; k < NUM_MONTHS; k++) {
        if (MONTH_DAYS[k] > day) {
            day++;
            month = static_cast<unsigned short>(k + START_MONTH);
            break;
        } else
            day -= MONTH_DAYS[k];
    }

    return timestamp;
}

/*
 * Converts a date from standard terms to a timestamp. A timestamp is the sum of
 * every minute that has passed since the 1st of May 2015 at 00:00.
 */
unsigned int Event::toTimestamp(unsigned short month, unsigned short day,
                                unsigned short hour, unsigned short minute) {
    unsigned int timestamp =
            static_cast<unsigned int>((day - 1) * 24 * 60 + hour * 60 + minute);
    for (unsigned short i = 0; i < month - START_MONTH; i++)
        timestamp += static_cast<unsigned int>(MONTH_DAYS[i] * 24 * 60);
    return timestamp;
}