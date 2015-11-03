#ifndef EVENTLINK_H
#define EVENTLINK_H

class EventLink {
public:
    EventLink();
    EventLink(unsigned short day7, unsigned int index);

    unsigned short day7() const;
    unsigned int index() const;

protected:
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
};

#endif // EVENTLINK_H
