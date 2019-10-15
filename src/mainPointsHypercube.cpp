#include <iostream>
#include "hasher.h"
#include "Hypercube.h"
#include "ui.h"

using namespace std;

Hypercube<PointHasher>* lsh;

int main(int argc, char* argv[]){

    lsh = new Hypercube<PointHasher>;

    /**
     * read arguments
     */
    readArgumentsCube(argc, argv);

    /**
     * ask input filename (if not given as an argument)
     */
    if(!lsh->isInputFileGiven())
        askInputFile();

}
