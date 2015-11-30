#include "HashTable.h"

/*
 * Initializes all the buckets (which have 0 elements initially).
 */
HashTable::HashTable(unsigned short mod, unsigned short size) :
        modulo(mod), bucketSize(size) {
    buckets = new unsigned short*[mod];
    bucketsNumElements = new unsigned short[mod];
    for (unsigned short i = 0; i < mod; i++) {
        buckets[i] = new unsigned short[size];
        bucketsNumElements[i] = 0;
    }
}

/*
 * Deletes every bucket and element counter array.
 */
HashTable::~HashTable() {
    for (unsigned short i = 0; i < modulo; i++)
        delete[] buckets[i];
    delete[] buckets;
    delete[] bucketsNumElements;
}

/*
 * Hashes the key then appends the value to the bucket.
 */
void HashTable::add(unsigned int key, unsigned short value) {
    unsigned short i = hash(key);
    buckets[i][bucketsNumElements[i]] = value;
    bucketsNumElements[i]++;
}

/*
 * Hashes the key then looks up the number of elements for its corresponding
 * bucket.
 */
unsigned short HashTable::entries(unsigned int key) const {
    unsigned short i = hash(key);
    return bucketsNumElements[i];
}

/*
 * Hashes the key then tries to return a value from the bucket at that index.
 * The index is not checked against the number of entries, and the returned
 * value could point to an uninitialized value.
 */
unsigned short HashTable::get(unsigned int key, unsigned short index) const {
    unsigned short i = hash(key);
    return buckets[i][index];
}

/*
 * Hashes the value, which can now fit inside a short, then returns it.
 */
unsigned short HashTable::hash(unsigned int value) const {
    return static_cast<unsigned short>(value % modulo);
}
