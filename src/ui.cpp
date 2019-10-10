#include <iostream>
#include <getopt.h>
#include <sstream>
#include <fstream>
#include "ui.h"
#include "utils.h"
#include "Dataset.h"

using namespace std;

void readArgumentsLSH(LSH* lsh, int argc, char **argv) {
    int c;
    while((c = getopt(argc, argv, "d:q:k:L:o:")) != -1){
        switch (c){
            case 'd':
                lsh->setInputFileGiven(true);
                lsh->setInputFilename(optarg);
                break;
            case 'q':
                lsh->setQueryFileGiven(true);
                lsh->setQueryFilename(optarg);
                break;
            case 'k':
                lsh->setNumOfFunctions(stoi(optarg));
                break;
            case 'L':
                lsh->setNumOfHashTables(stoi(optarg));
                break;
            case 'o':
                lsh->setOutputFileGiven(true);
                lsh->setOutputFilename(optarg);
                break;
            default:
                cout << "Non acceptable argument, exiting..." << endl;
                exit(-1);
        }
    }
}

void parseInputFilePoints(LSH* lsh) {
    if(!file_exists(lsh->getInputFilename().c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new DatasetPoints();
    cout << "Parsing input file: " << lsh->getInputFilename() << ", please wait..." << endl;
    ifstream inputFile(lsh->getInputFilename().c_str());
    string line;
    int size = 0;
    int current_dimension = -1;
    while(getline(inputFile, line)){
        //extract item_id
        string item_id = line.substr(0, line.find(' '));
        auto point = new Point(item_id);
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
    lsh->setData(data);
}
