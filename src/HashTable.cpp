#include <cstdio>
#include "HashTable.h"

HashTableList::HashTableList(int numOfHTs, int sizeOfHTs) {
    for (int i = 0; i < numOfHTs; ++i) {
        printf("Creating number %d ht\n", i);
        hashTableList.push_back(new HashTable(sizeOfHTs));
    }
}

HashTableList::~HashTableList() {
    std::list<HashTable*>::iterator it;
    for(it = hashTableList.begin(); it != hashTableList.end(); ++it){
        delete *it;
    }
}

HashTable::HashTable(int size) {
    this->size = size;
}

HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        std::list<Object*>::iterator it;
        for(it = buckets[i].begin(); it != buckets[i].end(); ++it){
            delete *it;
        }
    }
}
