#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#define ASCEND 1
#define DESCEND 0
#define cmp1(a, b) ((a > b) ? 1 : 0)

int main() {
    
}

void mergeSort(int* array, int lenth, int* left, int* right) {
    int halfLenth;
    if (lenth == 1) {
        *left = array[0];
    } else {
        halfLenth = lenth / 2;
        left = (int*) malloc((halfLenth + 1) * sizeof(int));
        right = (int*) malloc((halfLenth + 2) * sizeof(int));
    }
}

/* If AorD == 0, sorting as descend, else as ascend */
int cmp(int a, int b, const int AorD) {
    if (AorD == DESCEND) 
        return a > b;
    else                //ASCEND
        return a < b;
}