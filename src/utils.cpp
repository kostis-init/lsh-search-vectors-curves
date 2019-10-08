//#include <stdio.h>


//computes base^exp % div , without using pow().This
// func ensures no overflow will occur during the above
// computation.Optimized with a divided & concquer technique.
int powModulo(int base,int exp,int div) {
    if (exp == 1) {
        return base % div;
    } else if (exp % 2 == 0) {
        return (powModulo(base,exp/2,div)*powModulo(base,exp/2,div)) % div;
    } else {
        return (powModulo(base,exp-1,div)*powModulo(base,1,div)) % div;
    }
}