#include "EventLink.h"

EventLink::EventLink() : byte1(0), byte2(0), byte3(0), byte4(0) {
}

EventLink::EventLink(unsigned short day7, unsigned int index) {
    byte1 = (unsigned char) (((day7 & 7) << 5) | ((index >> 24) & 0x1F));
    byte2 = (unsigned char) ((index >> 16) & 0xFF);
    byte3 = (unsigned char) ((index >> 8) & 0xFF);
    byte4 = (unsigned char) (index & 0xFF);
}

unsigned short EventLink::day7() const {
    return (unsigned short) ((byte1 >> 5) & 7);
}

unsigned int EventLink::index() const {
    return (unsigned int) (((byte1 & 0x1F) << 24) | (byte2 << 16) | byte3 << 8 |
            byte4);
}
