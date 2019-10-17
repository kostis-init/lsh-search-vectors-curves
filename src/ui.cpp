#include <iostream>
#include <getopt.h>
#include <algorithm>
#include "utils.h"
#include "Dataset.h"
#include "LSH.h"
#include "Cube.h"

using namespace std;

class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

void readArgumentsLSHPoints(LSH* lsh, int argc, char **argv) {
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
    if (!lsh->getNumOfFunctions())
        lsh->setNumOfFunctions(4);
    if  (!lsh->getNumOfHashTables())
        lsh->setNumOfHashTables(5);
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
    if (!cube->getLsh()->getNumOfHashTables())
       cube->getLsh()->setNumOfHashTables(3);
}   

void readArgumentsLSHCurves(LSH* lsh, int argc, char **argv) {

    auto parser = new InputParser(argc,argv);
    if (parser->cmdOptionExists("-d"))
        lsh->setInputFilename(parser->getCmdOption("-d"));
    if (parser->cmdOptionExists("-q"))
        lsh->setQueryFilename(parser->getCmdOption("-q"));
    if (parser->cmdOptionExists("-o"))
        lsh->setOutputFilename(parser->getCmdOption("-o"));
    if (parser->cmdOptionExists("-k_vec"))
        lsh->setNumOfFunctions(stoi(parser->getCmdOption("-k_vec")));
    else 
        lsh->setNumOfFunctions(1);
    if (parser->cmdOptionExists("-L_grid"))
        lsh->setNumOfHashTables(stoi(parser->getCmdOption("-L_grid")));
    else 
        lsh->setNumOfHashTables(4);
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
