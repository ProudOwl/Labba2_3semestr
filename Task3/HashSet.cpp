#include "HashSet.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

HashNode::HashNode(const string& k) : key(k), next(nullptr) {}

HashSet::HashSet() : count(0) {
    table = new HashNode*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

// Конструктор копирования
HashSet::HashSet(const HashSet& other) : count(0) {
    table = new HashNode*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    
    // Копируем все элементы из other
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = other.table[i];
        while (current != nullptr) {
            SETADD(current->key);
            current = current->next;
        }
    }
}

// Оператор присваивания
HashSet& HashSet::operator=(const HashSet& other) {
    if (this != &other) {
        // Очищаем текущие данные
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
        
        // Копируем из other
        count = 0;
        table = new HashNode*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = other.table[i];
            while (current != nullptr) {
                SETADD(current->key);
                current = current->next;
            }
        }
    }
    return *this;
}

unsigned int HashFunction(const string& key) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;
    }
    return hash % HashSet::TABLE_SIZE;
}

// Добавление элемента
void HashSet::SETADD(const string& key) {
    if (SET_AT(key)) {
        return;
    }
    
    unsigned int index = HashFunction(key);
    HashNode* newNode = new HashNode(key);
    
    // Добавляем в начало списка
    newNode->next = table[index];
    table[index] = newNode;
    count++;
}

// Удаление элемента
void HashSet::SETDEL(const string& key) {
    unsigned int index = HashFunction(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                // Удаляем первый элемент списка
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            count--;
            cout << "Элемент '" << key << "' удален" << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    
    cout << "Элемент '" << key << "' не найден" << endl;
}

// Проверка наличия элемента
bool HashSet::SET_AT(const string& key) const {
    unsigned int index = HashFunction(key);
    HashNode* current = table[index];
    
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Деструктор
HashSet::~HashSet() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}
