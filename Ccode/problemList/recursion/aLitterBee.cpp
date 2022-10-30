// Finished

#include<iostream>
#include<cstdio>

using namespace std;

int main() {
    long i, n;
    long src, dst;
    long a[55] = {-1, 0, 1, 2, 3};
    for (i = 5; i < 55; i++) {
        a[i] = a[i-1] + a[i-2];
    }
    scanf("%ld", &n);
    for (i = 0; i < n; i++) {
        scanf("%ld %ld", &src, &dst);
        printf("%ld\n", a[1 + dst - src]);
    }
    return 0;
}


/*  notion:
    Becareful with the scale.
*/