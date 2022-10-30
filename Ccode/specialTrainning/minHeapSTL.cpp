#include<queue>
#include<iostream>
#include<functional>
#include<ctime>
#include<cstdlib>
using namespace std;
 
priority_queue<int> pq1; //默认最大堆 
priority_queue<int,vector<int>,greater<int> > pq2; //最小堆 
/** addition 
equal_to       相等 
not_equal_to   不相等 
less           小于 
greater        大于 
less_equal     小于等于 
greater_equal 大于等 
这些在所有的排序算法中同样适用 
*/
int main()
{
    srand(time(NULL));
    for(int i=0;i<20;i++)
    {
      int r= rand()%10000;
      pq1.push(r);
      pq2.push(r);
    }
    
    for(int i=0;i<20;i++)
    {
         cout<<pq1.top()<<" "<<pq2.top()<<endl;
         pq1.pop();
         pq2.pop();
    }
    cin.get();
    return 0;
} 