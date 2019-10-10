#include <iostream>
#include "HashTableStruct.h"
#include "hasher.h"

HashTableStruct::HashTableStruct(int numOfHTs) {
    this->numOfHTs = numOfHTs;
    this->hashTables = new unordered_set<Object *, PointHasher>[numOfHTs];
}
HashTableStruct::~HashTableStruct() {
    delete[] hashTables;
}

void HashTableStruct::addToAllHashTables(Object *obj) {
    for (int i = 0; i < numOfHTs; ++i) {
        this->hashTables[i].insert(obj);
    }
}

void HashTableStruct::addToHashTable(int ht_index, Object * obj) {
    this->hashTables[ht_index].insert(obj);
}


