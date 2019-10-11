#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include "utils.h"

using namespace std;

// computes base^exp % div , without using pow().This
// func ensures no overflow will occur during the above
// computation.Optimized with a divided & conquer technique.
int powModulo(int base,int exp,int div) {
    if (exp == 1) {
        return base % div;
    } else if (exp % 2 == 0) {
        return (powModulo(base,exp/2,div)*powModulo(base,exp/2,div)) % div;
    } else {
        return (powModulo(base,exp-1,div)*powModulo(base,1,div)) % div;
    }
}

// check if file exists
bool file_exists(const char* filename){
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}

bool is_number(string s)
{
    return !s.empty() &&
            find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void test_print_hashtable(HashTableStruct *hashTableStruct) {
    auto hts = hashTableStruct->getAllHashTables();
    for (int i = 0; i < hashTableStruct->getNumOfHTs(); i++) {
        auto fn = hts[i].hash_function();
        cout << "\nHASH TABLE " << i + 1 << endl;
        for(auto entry : hts[i]){
            cout << "Item Id: " << entry->getId();
            cout << ",\thash func: " << fn(entry);
            cout << ",\tbucket #" << hts[i].bucket(entry);
            cout << ",\tbucket count: " << hts[i].bucket_count();
            cout << endl;
        }
    }
}
void test_print_data(DatasetPoints *data) {
    auto points = data->getPoints();
    for (int i = 0; i < points.size(); i++) {
        cout << "CHECKING ITEM ID: " << points[i]->getId() << endl;
        auto coords = points[i]->getCoordinates();
        for (int j = 0; j < coords.size(); ++j) {
            cout << coords[j] << " ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << endl;
}

double min(double coordinate,double min) {
    return coordinate < min ? coordinate : min;
}

double max(double coordinate,double max) {
    return coordinate > max ? coordinate : max;
}