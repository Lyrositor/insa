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
    /**
     * Initializes the hash table with its hashing parameters and bucket size.
     *
     * The modulo value also specifies how many buckets will be created to hold
     * all possible key-value pairs.
     * @param mod the value of the modulo used to hash keys
     * @param size the maximum size of a bucket
     */
    HashTable(unsigned short mod, unsigned short size);

    /**
     * Destructs the hash table and all its buckets.
     */
    virtual ~HashTable();

    /**
     * Adds a new key-value association to the hash table.
     *
     * @param key the ID used to look up the value
     * @param value the value to store under the specified key
     */
    void add(unsigned int key, unsigned short value);

    /**
     * Returns the number of values stored for a certain key.
     *
     * Usually equal to 1 in good situations; any value superior to 1 indicates
     * a hash collision. The entries must be iterated over to find the correct
     * one.
     * @param key the ID to look up
     * @return the number of entries in the specified key's bucket
     */
    unsigned short entries(unsigned int key) const;

    /**
     * Gets the value corresponding to the specified key, at the specified index
     * in the bucket.
     *
     * @param key the ID to look up
     * @param index the index of the value in the key's bucket
     * @return the value stored at that index in the key's bucket
     */
    unsigned short get(unsigned int key, unsigned short index) const;

protected:
    /**
     * The modulo value used by the hash function.
     */
    unsigned short modulo;

    /**
     * The size to allocate for each key's bucket.
     *
     * The size should be sufficient to handle a worst-case scenario where every
     * key creates a collision in the same bucket.
     */
    unsigned short bucketSize;

    /**
     * The array of key buckets.
     *
     * The number of buckets corresponds to the modulo value.
     */
    unsigned short** buckets;

    /**
     * The number of elements in each bucket.
     *
     * Incremented every time a value is added to a bucket until it is full.
     */
    unsigned short* bucketsNumElements;

    /**
     * Hashes the provided value and returns its hash.
     *
     * The hash function performs a simple modulo operation on the value and
     * returns the result.
     * @param value the value to hash
     * @return the hashed value
     */
    unsigned short hash(unsigned int value) const;
};

#endif // HASHTABLE_H
