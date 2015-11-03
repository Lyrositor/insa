#include "HashTable.h"

HashTable::HashTable(unsigned short modulo, unsigned short bucketSize) :
        modulo(modulo), bucketSize(bucketSize) {
    buckets = new unsigned short*[modulo];
    bucketsNumElements = new unsigned short[modulo];
    for (unsigned short i = 0; i < modulo; i++) {
        buckets[i] = new unsigned short[bucketSize];
        bucketsNumElements[i] = 0;
    }
}

HashTable::~HashTable() {
    for (unsigned short i = 0; i < modulo; i++)
        delete[] buckets[i];
    delete[] buckets;
    delete[] bucketsNumElements;
}

void HashTable::add(unsigned int key, unsigned short value) {
    unsigned short i = hash(key);
    buckets[i][bucketsNumElements[i]] = value;
    bucketsNumElements[i]++;
}

unsigned short HashTable::entries(unsigned int key) const {
    unsigned short i = hash(key);
    return bucketsNumElements[i];
}

unsigned short HashTable::get(unsigned int key, unsigned short j) const {
    unsigned short i = hash(key);
    return buckets[i][j];
}

unsigned short HashTable::hash(unsigned int value) const {
    return (unsigned short) (value % modulo);
}
