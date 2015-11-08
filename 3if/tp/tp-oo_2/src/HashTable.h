#ifndef HASHTABLE_H
#define HASHTABLE_H

/**
 * A hash table for storing shorts.
 *
 * Provides an associative array between an integer and a short. In the case of
 * a collision, the returned values must be iterated over to find the desired
 * one.
 */
class HashTable {
public:
    HashTable(unsigned short mod, unsigned short size);
    virtual ~HashTable();

    void add(unsigned int key, unsigned short value);
    unsigned short entries(unsigned int key) const;
    unsigned short get(unsigned int key, unsigned short index) const;

protected:
    unsigned short modulo;
    unsigned short bucketSize;
    unsigned short** buckets;
    unsigned short* bucketsNumElements;

    unsigned short hash(unsigned int value) const;
};

#endif // HASHTABLE_H
