#include <iostream>
#include <cstring>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "utils.h"

using namespace std;

//input arguments
static char inputFilename[128];
static char queryFilename[128];
static char outputFilename[128];
static int numOfFunctions = 4;
static int numOfHashTables = 5;
void readArguments(int argc, char* argv[]);

//dataset
static DatasetPoints* data;
void parseInputFile();

void test_print_data();

int main(int argc, char* argv[]){

    //read input arguments
    readArguments(argc, argv);

    //read input file if not given as argument


    //read input file and store data in memory
    parseInputFile();

    test_print_data();

    //construct hash tables & hash functions
    HashTableStruct* hashTableStruct = new HashTableStruct(numOfHashTables);


    //do the query

    //+more
    //+check memory leaks

    return 0;
}

void test_print_data() {
    auto points = data->getData();
    for (int i = 0; i < points.size(); i+=100) {
        cout << "CHECKING ITEM ID: " << points[i]->getId() << endl;
        auto coords = points[i]->getCoordinates();
        for (int j = 0; j < coords.size(); ++j) {
            cout << coords[j] << " ";
        }
        cout << endl;
    }
    cout << data->getDimension() << " " << data->getSize() << endl;
}

void readArguments(int argc, char* argv[]) {
    int c;
    while((c = getopt(argc, argv, "d:q:k:L:o:")) != -1){
        switch (c){
            case 'd':
                strcpy(inputFilename, optarg);
                break;
            case 'q':
                strcpy(queryFilename, optarg);
                break;
            case 'k':
                numOfFunctions = stoi(optarg);
                break;
            case 'L':
                numOfHashTables = stoi(optarg);
                break;
            case 'o':
                strcpy(outputFilename, optarg);
                break;
            default:
                cout << "Non acceptable argument, exiting..." << endl;
                exit(-1);
        }
    }
}

void parseInputFile() {
    if(!file_exists(inputFilename)){
        cout << "input file does not exist" << endl;
        exit(-1);
    }
    data = new DatasetPoints();
    cout << "Parsing input file: " << inputFilename << ", please wait..." << endl;
    ifstream inputFile(inputFilename);
    string line;
    int size = 0;
    int current_dimension = -1;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find(' '));
        Point* point = new Point(item_id);
        //keep only the coordinates
        line = line.substr(line.find(' ') + 1);
        string token;
        stringstream line_stream;
        line_stream << line;
        int dimension = 0;
        //add every coordinate to point
        while(getline(line_stream, token, ' ')){
            if(!is_number(token))
                continue;
            point->addCoordinateLast(atof(token.c_str()));
            dimension++;
        }
        if(current_dimension != -1 && current_dimension != dimension){
            cout << "Error in input file, non stable dimension" << endl;
        }
        current_dimension = dimension;
        size++;
        data->addPoint(point);
    }
    data->setSize(size);
    data->setDimension(current_dimension);
}
