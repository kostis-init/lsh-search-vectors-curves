#include <iostream>
#include <cstring>
#include <getopt.h>
#include "HashTable.h"

//input arguments
static char inputFilename[128];
static char queryFilename[128];
static char outputFilename[128];
static int numOfFunctions = 4;
static int numOfHashTables = 5;

void readArguments(int argc, char* argv[]);

int main(int argc, char* argv[]){

    //read input arguments
    readArguments(argc, argv);

    //read input files and store data in memory

    //construct hash tables & hash functions
    int sizeOfHashTables = 100;
    HashTableList* hashTableList = new HashTableList(numOfHashTables, sizeOfHashTables);


    //do the query

    //+more

    return 0;
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
                numOfFunctions = std::stoi(optarg);
                break;
            case 'L':
                numOfHashTables = std::stoi(optarg);
                break;
            case 'o':
                strcpy(outputFilename, optarg);
                break;
            default:
                printf("Non acceptable argument, exiting...");
                exit(-1);
        }
    }
}


