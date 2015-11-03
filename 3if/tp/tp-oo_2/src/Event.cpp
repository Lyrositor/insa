#include "config.h"
#include "Event.h"

Event::Event() : byte1(0), byte2(0), byte3(0), byte4(0) {
}

Event::Event(
        unsigned short sensorIndex, unsigned short state,
        unsigned short month, unsigned short day, unsigned short hour,
        unsigned short minute) {
    // Convert the date to a timestamp.
    unsigned int timestamp = toTimestamp(month, day, hour, minute);

    byte1 = (unsigned char) (((state & 3) << 6));
    byte1 |= (unsigned char) ((sensorIndex >> 5) & 0x3F);
    byte2 = (unsigned char) (sensorIndex & 0x1F) << 3;
    byte2 |= ((timestamp >> 16) & 7);
    byte3 = (unsigned char) ((timestamp >> 8) & 0xFF);
    byte4 = (unsigned char) (timestamp & 0xFF);
}

unsigned short Event::sensorIndex() const {
    return (unsigned short) (((byte1 & 0x3F) << 5) | ((byte2 >> 3) & 0x1F));
}

unsigned short Event::state() const {
    return (unsigned short) ((byte1 >> 6) & 3);
}

unsigned int Event::date() const {
    return (unsigned int) (((byte2 & 7) << 16) | (byte3 << 8) | byte4);
}

unsigned int Event::date(
        unsigned short& month, unsigned short& day, unsigned short& hour,
        unsigned short& minute) const {
    unsigned int timestamp = date();
    minute = (unsigned short) (timestamp % 60);
    hour = (unsigned short) (((timestamp - minute)/60) % 24);
    day = (unsigned short) ((timestamp - minute - hour*60)/(24 * 60));

    month = 0;
    for (unsigned int k = 0; k < NUM_MONTHS; k++) {
        if (MONTH_DAYS[k] > day) {
            day++;
            month = (unsigned short) (k + START_MONTH);
            break;
        } else
            day -= MONTH_DAYS[k];
    }

    return timestamp;
}

unsigned int Event::toTimestamp(unsigned short month, unsigned short day,
                                unsigned short hour, unsigned short minute) {
    unsigned int timestamp =
            (unsigned int) (day - 1) * 24 * 60 + hour * 60 + minute;
    for (unsigned short i = 0; i < month - START_MONTH; i++)
        timestamp += MONTH_DAYS[i] * 24 * 60;
    return timestamp;
}