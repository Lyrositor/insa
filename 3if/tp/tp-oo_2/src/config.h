/** @file config.h
 * A list of configuration values for the entire program. */
#ifndef CONFIG_H
#define CONFIG_H

/** The maximum number of events which can be added. */
const unsigned int MAX_EVENTS = 20000000;

/** The maximum amount of unique sensors which can exist. */
const unsigned short MAX_SENSORS = 1500;

/** The number of days in a week. */
const unsigned short NUM_DAYS = 7;

/** The size of a segment of events (for the segmented table). */
const unsigned int EVENT_SEGMENT_SIZE = (int) (MAX_EVENTS/NUM_DAYS) + 1;

/** The size of a segment of event links (for the segmented table). */
const unsigned int EVENT_LINK_SEGMENT_SIZE = (int) (MAX_EVENTS/MAX_SENSORS) + 1;

/** The list of possible states. */
const unsigned char STATES[] = {'V', 'J', 'R', 'N'};

/** The only authorized year for events. */
const unsigned short YEAR = 2015;

/** The number of months to accept events from. */
const unsigned short NUM_MONTHS = 5;

/** The number of the starting month to accept events from.
 *
 * Numbering starts at 1 (for January), then moves on to 2 (for February) and so
 * on.
 */
const unsigned short START_MONTH = 5;

/** The number of the ending month to accept events from. */
const unsigned short END_MONTH = START_MONTH + NUM_MONTHS - 1;

/** The number of days per month of the year (May to September). */
const unsigned short MONTH_DAYS[] = {
        31,
        30,
        31,
        31,
        30
};

#endif // CONFIG_H
