// Finished

#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int myTime = 0;
int tasks = 0;

typedef struct a {
    int start;
    int end;
} activity;

bool cmp(activity act1, activity act2) {
    return act1.end < act2.end;
}

int main() {
    activity act[2000];
    int i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &act[i].start);
        scanf("%d", &act[i].end);
    }
    sort(act, act+n, cmp);
    for (i = 0; i < n; i++) {
        if (myTime <= act[i].start) {
            myTime = act[i].end;
            tasks++;
        }
    }
    printf("%d\n", tasks);
    return 0;
}

/* Gready: End time first.*/
