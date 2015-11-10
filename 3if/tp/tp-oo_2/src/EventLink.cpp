#include "EventLink.h"

/*
 * Initializes an empty event link.
 */
EventLink::EventLink() : byte1(0), byte2(0), byte3(0), byte4(0) {
}

/*
 * Performs some bit-arithmetic to store a link's data into as little space as
 * as possible. The day takes up 3 bits while the timestamp takes up 29 bits.
 */
EventLink::EventLink(unsigned short d7, unsigned int idx) {
    byte1 = static_cast<unsigned char>(((d7 & 7) << 5) | ((idx >> 24) & 0x1F));
    byte2 = static_cast<unsigned char>((idx >> 16) & 0xFF);
    byte3 = static_cast<unsigned char>((idx >> 8) & 0xFF);
    byte4 = static_cast<unsigned char>(idx & 0xFF);
}

/*
 * Retrieves the linked event's day from its 3-bit structure and returns it as a
 * short instead.
 */
unsigned short EventLink::day7() const {
    return static_cast<unsigned short>((byte1 >> 5) & 7);
}

/*
 * Retrieves the linked event's index from its 22-bit structure and returns it
 * as an integer instead.
 */
unsigned int EventLink::index() const {
    return static_cast<unsigned int>(((byte1 & 0x1F) << 24) | (byte2 << 16) |
            byte3 << 8 | byte4);
}
