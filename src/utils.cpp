#include <sys/stat.h>
#include <algorithm>
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
bool file_exists(char* filename){
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}

bool is_number(string s)
{
    return !s.empty() &&
            find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}