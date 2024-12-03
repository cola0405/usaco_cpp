// 贪心+单调栈+状态压缩
// 贪心的策略是，从高到低处理cow，先从塔底开始，每次把当前最高的分到各堆 -- 通过单调栈来实现

// 双端队列前面的是w更大的
// 拿一个测试用例实际走一遍就理解了

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
    sort(cows.begin(), cows.end(), cmp);            // 从大到小排序
    deque<pair<int, int>> deq = {{INT_MAX, m}};     // deq[i].second 表示塔顶为 deq[i].first 的塔的数量
    long long ans = 0;
    for(auto it: cows){     // 先从塔底开始，每次把当前最高的分到各堆
        int w=it.first, a=it.second;
        while(a>0 && w+k <= deq.front().first){     
            if(deq.empty()) break;          // 当前w重量的牛把所有塔顶都覆盖了，那此时deq就是空的
            if(a >= deq.front().second){    
                a -= deq.front().second;    
                deq.pop_front();            // 当前w重量的牛数量多，足以把塔顶为deq.front 的都覆盖，front 就可以删除了
            }else{
                deq.front().second -= a;    // 当前w重量的牛不够分，那就能覆盖几个是几个
                a=0;
            }
        }
        deq.push_back(make_pair(w, it.second-a));       // 当前以w重量的牛作塔顶的塔的数量
        ans += it.second-a;        // 这些成为塔顶的牛就是入塔的牛的数量
    }
    cout<<ans<<endl;
}