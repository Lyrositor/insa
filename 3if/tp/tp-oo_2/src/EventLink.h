#ifndef EVENTLINK_H
#define EVENTLINK_H

/**
 * Represents a link to a stored event.
 *
 * A link consists of a day of the week (0 - 6) and the event's index within
 * the day's event table.
 */
class EventLink {
public:
    /**
     * Initializes a void link to an event.
     *
     * By default, this links to the first element of the first day, but such a
     * link should be explicitly initialized instead.
     */
    EventLink();

    /**
     * Initializes a link to a certain event on a certain day.
     *
     * @param d7 the event's day of the week (from 0 to 6)
     * @param idx the event's index in the day's table
     */
    EventLink(unsigned short d7, unsigned int idx);

    /**
     * Returns the linked event's day of the week.
     *
     * @return the linked event's day of the week
     */
    unsigned short day7() const;

    /**
     * Returns the linked event's index in the day's table.
     *
     * @return the linked event's index in the day's table
     */
    unsigned int index() const;

protected:
    /**
     * The highest order byte (stores the day and part of the index).
     */
    unsigned char byte1;

    /**
     * The second-highest order byte (stores part of the index).
     */
    unsigned char byte2;

    /**
     * The third-highest order byte (stores part of the index).
     */
    unsigned char byte3;

    /**
     * The fourth-highest order byte (stores part of the index).
     */
    unsigned char byte4;
};

#endif // EVENTLINK_H
