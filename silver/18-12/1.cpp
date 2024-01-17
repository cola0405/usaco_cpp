// 二分lowerbound解决最值问题

// 求解：让牛的等待时间尽可能少，然后求其中的最大值
// 首选贪心、二分
// 然后面临一个问题 —— 对于cow[i] 到底是坐当前这辆车，还是下一辆 —— 难有贪心的依据

// 换个思路
// 在推导测试用例的时候不难发现 —— 牛的等待时间其实就是一个bus内 first 和 last 的到达的时间差
// 那我们其实可以用 wait time 去套，看是否能够运完所有的牛 —— 二分找lowerbound

#include<bits/stdc++.h>
using namespace std;

int n,m,c,ti;
vector<int> t;

bool transport_all(int wait){
    int cur = 0;
    for(int i=0; i<m; i++){
        int available = c, start = t[cur];
        while(cur<n && available>0 && t[cur]-start <= wait){
            cur++;
            available--;
        }
    }
    return cur == n;
}

int main(){
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    cin>>n>>m>>c;
    for(int i=0; i<n; i++){
        cin>>ti;
        t.push_back(ti);
    }
    sort(t.begin(), t.end());
    int low = 1;
    int high = t.back() - t.front();
    while(low<high){    // binary search the lower bound of the wait time of the bus 
        int mid = (low+high)/2;
        if(transport_all(mid)) high = mid;
        else low = mid+1;
    }
    cout<<low<<endl;
}