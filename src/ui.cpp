#include <iostream>
#include <getopt.h>
#include <sstream>
#include <fstream>
#include <cfloat>
#include "ui.h"
#include "utils.h"
#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"

using namespace std;

void readArgumentsLSH(LSH<PointHasher>* lsh, int argc, char **argv) {
    int c;
    while((c = getopt(argc, argv, "d:q:k:L:o:")) != -1){
        switch (c){
            case 'd':
                lsh->setInputFilename(optarg);
                break;
            case 'q':
                lsh->setQueryFilename(optarg);
                break;
            case 'k':
                lsh->setNumOfFunctions(stoi(optarg));
                break;
            case 'L':
                lsh->setNumOfHashTables(stoi(optarg));
                break;
            case 'o':
                lsh->setOutputFilename(optarg);
                break;
            default:
                cout << "Non acceptable argument, exiting..." << endl;
                exit(-1);
        }
    }
}

void readArgumentsCube(Cube<PointHasher>* cube, int argc, char **argv) {
    int c;
    while((c = getopt(argc, argv, "d:q:k:M:p:o:")) != -1){
        switch (c){
            case 'd':
                cube->getLsh()->setInputFilename(optarg);
                break;
            case 'q':
                cube->getLsh()->setQueryFilename(optarg);
                break;
            case 'k':
                cube->setDimension(stoi(optarg));
                break;
            case 'M':
                cube->setMaxChecked(stoi(optarg));
                break;
            case 'p':
                cube->setMaxProbes(stoi(optarg));
                break;
            case 'o':
                cube->getLsh()->setOutputFilename(optarg);
                break;
            default:
                cout << "Non acceptable argument, exiting..." << endl;
                exit(-1);
        }
    }
}

void askInputFile(){
    string filename;
    cout << "Please give input filename" << endl;
    cin >> filename;
    lsh->setInputFilename(filename);
}

void askQueryFile(){
    string filename;
    cout << "Please give query filename" << endl;
    cin >> filename;
    lsh->setQueryFilename(filename);
}

void askOutputFile(){
    string filename;
    cout << "Please give output filename" << endl;
    cin >> filename;
    lsh->setOutputFilename(filename);
}
