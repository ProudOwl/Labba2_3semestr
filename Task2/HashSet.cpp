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

// Хеш-функция (простой вариант)
unsigned int hashFunction(const string& key) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;
    }
    return hash % HashSet::TABLE_SIZE;
}

// Добавление элемента
void HashSet::SETADD(const string& key) {
    if (SET_AT(key)) {
        cout << "Элемент '" << key << "' уже существует" << endl;
        return;
    }
    
    unsigned int index = hashFunction(key);
    HashNode* newNode = new HashNode(key);
    
    // Добавляем в начало списка
    newNode->next = table[index];
    table[index] = newNode;
    count++;
    
    cout << "Элемент '" << key << "' добавлен" << endl;
}

// Удаление элемента
void HashSet::SETDEL(const string& key) {
    unsigned int index = hashFunction(key);
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
bool HashSet::SET_AT(const string& key) {
    unsigned int index = hashFunction(key);
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

// Обработка команды
void processCommand(HashSet& set, const string& command, const string& key) {
    if (command == "SETADD") {
        set.SETADD(key);
    } else if (command == "SETDEL") {
        set.SETDEL(key);
    } else if (command == "SET_AT") {
        bool exists = set.SET_AT(key);
        cout << "Элемент '" << key << "' " << (exists ? "найден" : "не найден") << endl;
    } else {
        cout << "Неизвестная команда: " << command << endl;
    }
}
