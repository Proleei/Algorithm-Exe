// Finished

#include<iostream>
#include<cstdio>

using namespace std;

struct uniq
{
    int a[1005];
};


int main() {
    int i, n, j;
    int sum1, sum2;
    uniq auniq[1005];

    scanf("%d", &n); // record the rows.
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            scanf("%d", &auniq[i].a[j]);
        }
    }

    for (i = n-1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            sum1 = auniq[i].a[j] + auniq[i-1].a[j];
            sum2 = auniq[i].a[j+1] + auniq[i-1].a[j];
            if (sum1 < sum2) {
                auniq[i-1].a[j] = sum2;
            } else {
                auniq[i-1].a[j] = sum1;
            }
        }
    }

    printf("%d\n", auniq[0].a[0]);
    return 0;
}

/*
    sum reversely
    upload the max result and update.
*/
