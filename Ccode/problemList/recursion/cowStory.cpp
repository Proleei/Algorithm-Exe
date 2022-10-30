// Finished!

#include<iostream>
#include<cstdio>

using namespace std;

int cowBorn(int year) {
    // exit condition.
    if (year < 5) {
        return year;
    }
    return cowBorn(year-1) + cowBorn(year-3);
}

int main() {
    int n;
    /*
    int i;
    FILE* fp1 = fopen("data.txt", "a+");
    for (i = 1; i < 55; i++) {
        fprintf(fp1, "%d, ", cowBorn(i));
    }
    fclose(fp1);
    */
    int a[100] = {-1, 1, 2, 3, 4, 6, 9, 13, 19, 28, 41, 60, 88, 129, 
                  189, 277, 406, 595, 872, 1278, 1873, 2745, 4023, 
                  5896, 8641, 12664, 18560, 27201, 39865, 58425, 
                  85626, 125491, 183916, 269542, 395033, 578949, 848491, 
                  1243524, 1822473, 2670964, 3914488, 5736961, 8407925, 
                  12322413, 18059374, 26467299, 38789712, 56849086, 83316385, 
                  122106097, 178955183, 262271568, 384377665, 563332848, 825604416};

    scanf("%d", &n);
    while (n != 0) {
        
        //int cowNum = cowBorn(n);
        //cout << cowNum << endl;
        printf("%d\n", a[n]); // Tips: do not use cout!
        scanf("%d", &n);
    }
    return 0;
}


/*  Reference link:
    https://zhidao.baidu.com/question/398610156.html
*/