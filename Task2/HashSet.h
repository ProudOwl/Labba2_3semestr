#ifndef HASHSET_H
#define HASHSET_H

#include <string>

using namespace std;

struct HashNode {
    string key;
    HashNode* next;
    
    HashNode(const string& k);
};

struct HashSet {
    static const int TABLE_SIZE = 1000;
    
    HashNode** table;
    int count;
    
    HashSet();
    void SETADD(const string& key);
    void SETDEL(const string& key);
    bool SET_AT(const string& key);
    ~HashSet();
};

unsigned int hashFunction(const string& key);
void processCommand(HashSet& set, const string& command, const string& key);

#endif
