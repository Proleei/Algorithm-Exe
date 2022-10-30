// Finished

#include<iostream>
#include<cstdio>

using namespace std;
/*
long factArray[51] = {-1, 1, 2, 6,};

// choose k's elements from n
long combination(long n, long k) {
    long up = factArray[n] /  factArray[n-k] ;
    long down =factArray[k];
    return up / down;
}
*/
int main() {
    long i, n;
    long angles;
    scanf("%ld", &n);
    for (i = 0; i < n; i++) {
        scanf("%ld", &angles);
        printf("%ld\n", angles*(2*angles-1) + 1);
    }
    
    return 0;
}

// edge equals vertex + 1
// use the combination(2 * angles, 2) + 1, while (2 * angles) equals to edge's number.  
