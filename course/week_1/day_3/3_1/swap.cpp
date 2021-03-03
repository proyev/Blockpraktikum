#include "swap.h"

void swapInt(int *num1, int *num2){
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void swapIntPointer(int **num1, int **num2){
    int *tmptr = *num1;
    *num1 = *num2;
    *num2 = tmptr;
}