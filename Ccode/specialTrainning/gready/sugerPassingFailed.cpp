#include<iostream>
#include<cstdio>

using namespace std;
long a[1000020];

int findLeast(int n) {
    long leastSuger = __LONG_MAX__;
    int leastPtr = -1;
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] < leastSuger) {
            leastSuger = a[i];
            leastPtr = i;
        }
    }
    return leastPtr;
}

int main() {
    int n;
    int i;
    int leastSugerPtr;
    int left, right;
    int step;
    long cost = 0;
    long sumOfSugers = 0;
    long average;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%ld", &a[i]);
        sumOfSugers += a[i];
    }
    average = sumOfSugers / n;
    leastSugerPtr = findLeast(n);
    
    while (a[leastSugerPtr] != average) {
        step = 0;
        left = leastSugerPtr;
        right = leastSugerPtr;
        while (a[left] <= average && a[right] <= average) {
            left = (left - 1 + n) % n;
            right = (right + 1) % n;
            step++;
        }
        if (a[left] > average) {
            a[left] -= 1;
            a[leastSugerPtr] += 1;
            cost += step;
        } else if (a[right] > average) {
            a[right] -= 1;
            a[leastSugerPtr] += 1;
            cost += step;
        }
        leastSugerPtr = findLeast(n);
    }
    printf("%ld\n", cost);
    return 0;
}


