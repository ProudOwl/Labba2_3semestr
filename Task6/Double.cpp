#include "HashTable.h"
#include <iostream>
#include <string>

int h1(int key) {
    return key % TABLE_SIZE;
}

int h2(int key) {
    return 1 + (key % (TABLE_SIZE - 1));
}

int doubleHash(int key, int attempt) {
    return (h1(key) + attempt * h2(key)) % TABLE_SIZE;
}

void initDoubleHashTable(struct DoubleHashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->keys[i] = EMPTY_MARKER;
        ht->values[i] = "";
    }
    ht->size = 0;
    ht->collisions = 0;
}

int doubleHashInsert(struct DoubleHashTable* ht, int key, const std::string& value) {
    if (ht->size >= TABLE_SIZE) {
        return -1;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = doubleHash(key, i);

        if (ht->keys[index] == EMPTY_MARKER || ht->keys[index] == DELETED_MARKER) {
            ht->keys[index] = key;
            ht->values[index] = value;
            ht->size++;
            return 1;
        }

        if (ht->keys[index] == key) {
            ht->values[index] = value;
            return 1;
        }

        ht->collisions++;
    }

    return -1;
}

int doubleHashSearch(struct DoubleHashTable* ht, int key, std::string& value) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = doubleHash(key, i);

        if (ht->keys[index] == EMPTY_MARKER) {
            return 0;
        }

        if (ht->keys[index] == key) {
            value = ht->values[index];
            return 1;
        }
    }

    return 0;
}

int doubleHashDelete(struct DoubleHashTable* ht, int key) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = doubleHash(key, i);

        if (ht->keys[index] == EMPTY_MARKER) {
            return 0;
        }

        if (ht->keys[index] == key) {
            ht->keys[index] = DELETED_MARKER;
            ht->size--;
            return 1;
        }
    }

    return 0;
}

double calculateLoadFactor(struct DoubleHashTable* ht) {
    return static_cast<double>(ht->size) / TABLE_SIZE;
}

void printDoubleHashTable(struct DoubleHashTable* ht) {
    std::cout << "Таблица двойного хеширования:\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->keys[i] != EMPTY_MARKER && ht->keys[i] != DELETED_MARKER) {
            std::cout << "Индекс " << i << ": Ключ=" << ht->keys[i]
                      << ", Значение=\"" << ht->values[i] << "\"\n";
        }
    }
    std::cout << "Коэффициент заполнения: " << calculateLoadFactor(ht) << "\n";
    std::cout << "Коллизии: " << ht->collisions << "\n";
}
