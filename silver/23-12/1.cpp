// 贪心+单调队列+状态压缩
// 贪心的策略是，从高到低处理cow，每次放到各堆中最厚实的 -- 通过单调栈来实现
// 拿一个测试用例实际走一遍1_1.py就理解了

// 1_2.cpp 是空间的优化

#include<bits/stdc++.h>
using namespace std;

bool cmp(const pair<int,int>& a, const pair<int,int>& b){
    return a.first > b.first;
}

int n,m,k;
int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    cin>>n>>m>>k;
    vector<pair<int, int>> cows;
    for(int i=0; i<n; i++){
        int w,a;
        cin>>w>>a;
        cows.push_back(make_pair(w,a));
    }
    sort(cows.begin(), cows.end(), cmp);
    deque<pair<int, int>> deq = {{INT_MAX, m}};     // 这个queue是按从大到小排序的
    long long ans = 0;
    for(auto it: cows){     // 状态压缩
        int w=it.first, a=it.second;
        while(a>0 && w+k <= deq.front().first){     // 和top的差距不足k，就不用看下去了
            if(deq.empty()) break;  // queue 有pop()操作, 需要做一个判定
            if(a >= deq.front().second){
                a -= deq.front().second;    // 数量a 顶在队首一个一个处理
                deq.pop_front();    
            }else{
                deq.front().second -= a;
                a=0;
            }
        }
        deq.push_back(make_pair(w, it.second-a));
        ans += it.second-a;     // 除了压缩queue，建塔的操作也要压缩
    }
    cout<<ans<<endl;
}