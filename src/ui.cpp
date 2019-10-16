#include <iostream>
#include <getopt.h>
#include "utils.h"
#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"

using namespace std;

void readArgumentsLSH(LSH* lsh, int argc, char **argv) {
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

//TODO: check -probes argument
void readArgumentsCube(Cube* cube, int argc, char **argv) {
    int c; int n;
    while((c = getopt(argc, argv, "d:q:k:M:p:o:")) != -1){
        switch (c){
            case 'd':
                cube->getLsh()->setInputFilename(optarg);
                break;
            case 'q':
                cube->getLsh()->setQueryFilename(optarg);
                break;
            case 'k':
                n = stoi(optarg);
                cube->setDimensionGiven(true);
                cube->setDimension(n);
                cube->getLsh()->setNumOfHashTables(n);
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

string askInputFile(){
    string filename;
    cout << "Please give input filename" << endl;
    cin >> filename;
    return filename;
}

string askQueryFile(){
    string filename;
    cout << "Please give query filename" << endl;
    cin >> filename;
    return filename;
}

string askOutputFile(){
    string filename;
    cout << "Please give output filename" << endl;
    cin >> filename;
    return filename;
}
