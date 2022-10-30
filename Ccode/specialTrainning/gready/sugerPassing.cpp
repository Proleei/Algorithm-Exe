// TODO: Find a nice gready strategy.

#include<iostream>
#include<cstdio>
#include<algorithm>

#define LEFT 0
#define RIGHT 1

struct node {
    bool towards;
    long distance;
    long candyNumber;
};

node a[1005];

int main() {
    int i, n;
    scanf("%d", n);
    for (i = 0; i < n; i++) {
        scanf("%ld", &a[i].candyNumber);
    }

    for (i = 0; i < n; i++) {

    }
    return 0;
}