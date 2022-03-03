#include "timer.h"

clock_t startTimer(){
    clock_t begin = clock();
    return begin;
}

clock_t endTimer(){
    clock_t end = clock();
    return end;
}

double timeSpent(){
    double spent = (double)(end-start)/CLOCKS_PER_SEC;
    return spent;
}   