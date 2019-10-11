#include <iostream>
#include <getopt.h>
#include <sstream>
#include <fstream>
#include <cfloat>
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

void askInputFile(LSH* lsh){
    string filename;
    cout << "Please give input filename" << endl;
    cin >> filename;
    lsh->setInputFilename(filename);
    lsh->setInputFileGiven(true);
}

DatasetPoints* parseInputFilePoints(string filename) {
    if(!file_exists(filename.c_str())){
        cout << "input file does not exist" << endl;
        exit(-1);
    };
    auto data = new DatasetPoints();
    cout << "Parsing input file: " << filename << ", please wait..." << endl;
    ifstream inputFile(filename.c_str());
    string line;
    int size = 0;
    int current_dimension = -1;
    double minCoordinate = DBL_MAX;
    double maxCoordinate = -DBL_MAX;
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
            auto coordinate = atof(token.c_str());
            minCoordinate = min(coordinate,minCoordinate);
            maxCoordinate = max(coordinate,maxCoordinate);
            point->addCoordinateLast(coordinate);
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
    data->setMaxCoordinate(maxCoordinate);
    data->setMinCoordinate(minCoordinate);
    return data;
}

void askQueryFile(LSH* lsh){
    string filename;
    cout << "Please give query filename" << endl;
    cin >> filename;
    lsh->setQueryFilename(filename);
    lsh->setQueryFileGiven(true);
}

void askOutputFile(LSH* lsh){
    string filename;
    cout << "Please give output filename" << endl;
    cin >> filename;
    lsh->setOutputFilename(filename);
    lsh->setOutputFileGiven(true);
}

QueryDatasetPoints* parseQueryFilePoints(string filename){

    //TODO

}