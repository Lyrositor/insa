#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    Event();
    Event(
            unsigned short sensorIndex, unsigned short state,
            unsigned short month, unsigned short day, unsigned short hour,
            unsigned short minute);

    unsigned short sensorIndex() const;
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
    unsigned char byte4;
};

#endif // EVENT_H
