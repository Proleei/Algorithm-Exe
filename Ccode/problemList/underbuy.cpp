// Thought wrongly.
// give up
#include<iostream>
#include<cstdio>
#include<queue>
#include<functional>

using namespace std;

struct PossibleChoice {
    long price;
    long times;
    long choice;

    friend bool operator < (PossibleChoice pc1, PossibleChoice pc2) {
        return pc1.times < pc2.choice; // MaxHeap.
    }
};

int main() {
    priority_queue<PossibleChoice> pq;
    //PossibleChoice pc[5005];
    PossibleChoice buffer[5005];
    PossibleChoice pc, pc2;
    long stocksPrice[5005];
    long i, j, n;
    long count = 0;
    long nowPrice;
    long maxTimes, maxCount;
    long size;
    scanf("%ld", &n);
    for (i = 0; i < n; i++) {
        scanf("%ld", &stocksPrice[i]);
    }

    pc.price = stocksPrice[n-1];
    pc.choice = 1;
    pc.times = 1;
    pq.push(pc);
    /*
    nowPrice = stocksPrice[n-1];
    pc[count].price = nowPrice;
    pc[count].times = 1;
    count++;
    */
    for (i = n-2; i >= 0; i--) {
        pc.price = stocksPrice[i-1];
        pc.choice = 1;
        pc.times = 1;
        size = pq.size();
        count = 0;
        for (j = 0; j < size; j++) {
            pc2 = pq.top();
            buffer[count] = pc2;
            count++;
            pq.pop();
            if (pc.price > pc2.price) {
                pc.choice
                break;
            } else if (pc[count - 1].price == pc[j].price) {
                pc[count - 1].times = pc[j].times;
                break;
            }
        }
    }
    /*
    for (i = 1; i < n; i++) {
        if (nowPrice < stocksPrice[i]) {
            nowPrice = stocksPrice[i];
            pc[count].price = nowPrice;
            pc[count].times = 1;
            count++;
        } else if (nowPrice == stocksPrice[i]) {
            continue;
        } else {
            j = count - 1;
            while (pc[j].price > stocksPrice[i]) {
                pc[j].times++;
                j--;
            }
        }
    }
    */
    maxTimes = pc[0].times;
    maxCount = 1;

    for (i = 1; i < count; i++) {
        if (maxTimes < pc[i].times) {
            maxTimes = pc[i].times;
            maxCount = 1;
        } else if (maxTimes == pc[i].times) {
            maxCount++;
        }
    }

    printf("%ld %ld\n", maxTimes, maxCount);
    return 0;
}
