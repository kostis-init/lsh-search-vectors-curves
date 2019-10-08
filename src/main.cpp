#include <iostream>
#include <unistd.h>


void readArguments(int argc, char* argv[]);

int main(int argc, char* argv[]){

    //read input arguments
    readArguments(argc, argv);


    //read input files and store data in memory

    //construct hash tables & hash functions

    //do the query

    //+more

    return 0;
}

void readArguments(int argc, char* argv[]) {
    int c;
    while( (c = getopt(argc, argv, "d::q::k::L::o::")) != -1){
        switch (c){
            case 'd':
                printf("d %s\n", optarg);
                break;
            case 'q':
                printf("q %s\n", optarg);
                break;
            case 'k':
                printf("k %s\n", optarg);
                break;
            case 'L':
                printf("L %s\n", optarg);
                break;
            case 'o':
                printf("o %s\n", optarg);
                break;
            default:
                printf("Non acceptable argument, exiting...");
                exit(-1);

        }
    }
}


