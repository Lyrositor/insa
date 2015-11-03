#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable {
public:
    HashTable(unsigned short modulo, unsigned short bucketSize);
    virtual ~HashTable();

    void add(unsigned int key, unsigned short value);
    unsigned short entries(unsigned int key) const;
    unsigned short get(unsigned int key, unsigned short j) const;

protected:
    unsigned short modulo;
    unsigned short bucketSize;
    unsigned short** buckets;
    unsigned short* bucketsNumElements;

    unsigned short hash(unsigned int value) const;
};

#endif // HASHTABLE_H
