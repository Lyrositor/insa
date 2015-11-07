#include "EventLink.h"

EventLink::EventLink() : byte1(0), byte2(0), byte3(0), byte4(0) {
}

EventLink::EventLink(unsigned short d7, unsigned int idx) {
    byte1 = static_cast<unsigned char>(((d7 & 7) << 5) | ((idx >> 24) & 0x1F));
    byte2 = static_cast<unsigned char>((idx >> 16) & 0xFF);
    byte3 = static_cast<unsigned char>((idx >> 8) & 0xFF);
    byte4 = static_cast<unsigned char>(idx & 0xFF);
}

unsigned short EventLink::day7() const {
    return static_cast<unsigned short>((byte1 >> 5) & 7);
}

unsigned int EventLink::index() const {
    return static_cast<unsigned int>(((byte1 & 0x1F) << 24) | (byte2 << 16) |
            byte3 << 8 | byte4);
}
