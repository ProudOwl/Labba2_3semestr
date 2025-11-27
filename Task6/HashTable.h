#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>

#define TABLE_SIZE 101
#define MAX_ITERATIONS 100
#define DELETED_MARKER -1
#define EMPTY_MARKER -2

struct DoubleHashTable {
    int keys[TABLE_SIZE];
    std::string values[TABLE_SIZE];
    int size;
    int collisions;
};

struct CuckooHashTable {
    int keys1[TABLE_SIZE];
    int values1[TABLE_SIZE];
    int keys2[TABLE_SIZE];
    int values2[TABLE_SIZE];
    int size;
    int collisions;
};

void initDoubleHashTable(struct DoubleHashTable* ht);
int doubleHashInsert(struct DoubleHashTable* ht, int key, const std::string& value);
int doubleHashSearch(struct DoubleHashTable* ht, int key, std::string& value);
int doubleHashDelete(struct DoubleHashTable* ht, int key);
double calculateLoadFactor(struct DoubleHashTable* ht);
void printDoubleHashTable(struct DoubleHashTable* ht);

void initCuckooHashTable(struct CuckooHashTable* ht);
int cuckooInsert(struct CuckooHashTable* ht, int key, int value);
int cuckooSearch(struct CuckooHashTable* ht, int key, int* value);
int cuckooDelete(struct CuckooHashTable* ht, int key);
double calculateCuckooLoadFactor(struct CuckooHashTable* ht);
void printCuckooHashTable(struct CuckooHashTable* ht);

#endif
