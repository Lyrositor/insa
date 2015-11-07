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
    EventLink();
    EventLink(unsigned short d7, unsigned int idx);

    unsigned short day7() const;
    unsigned int index() const;

protected:
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
};

#endif // EVENTLINK_H
