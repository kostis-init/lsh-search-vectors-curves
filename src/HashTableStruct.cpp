#include "HashTableStruct.h"

HashTableStruct::HashTableStruct(int numOfHTs) {
    this->numOfHTs = numOfHTs;
    this->hashTables = new unordered_map<int, vector<Object *>>[numOfHTs];
}
HashTableStruct::~HashTableStruct() {
    delete[] hashTables;
}


auto HashTableStruct::getAllHashTables() {
    return hashTables;
}

auto HashTableStruct::getHashTable(int index) {
    return hashTables[index];
}
