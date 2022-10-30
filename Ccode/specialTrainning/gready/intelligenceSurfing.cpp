// Finished

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<functional>
#include<cstdlib>

using namespace std;
priority_queue<int> pq1; // maxHeap
priority_queue<int,vector<int>,greater<int> > pq2; // minHeap

/** addition 
equal_to       相等 
not_equal_to   不相等 
less           小于 
greater        大于 
less_equal     小于等于 
greater_equal 大于等 
这些在所有的排序算法中同样适用 
*/

typedef struct a {
    int prize;
    int ddl;
} middle;

bool cmpDdl(middle m1, middle m2) { // Ascend
    return m1.ddl < m2.ddl;
}

int main() {
    middle mi[600];
    int money = 0;
    int timeLimit = 1;
    int count = 0;
    int n; // Number of middle.
    int i;
    
    scanf("%d %d", &money, &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &mi[i].ddl);
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &mi[i].prize);
    }
    
    sort(mi, mi+n, cmpDdl); // Sort as ddl Ascending.

    for (i = 0; i < n; i++) {
        timeLimit = mi[i].ddl;
        count++;
        pq2.push(mi[i].prize);
        if (timeLimit < count) {
            count--;
            money -= pq2.top(); // Retrun the minimal prize of the heap.
            pq2.pop();
        }
    }
    if (money < 0) {
        printf("%d\n", 0);
    } else {
        printf("%d\n", money);
    }

    return 0;
}

/*  
    Gready strategy:
        sort as ddl ascending.
        if count < timelimit then go on.
        else 
            choose the least prize from the counted middles, and delete it.
            so we always keep the minimal fine, max prize.
*/
